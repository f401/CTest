#define ENABLE_HTTPS

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#define PRINTF_ERROR(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define AUTO_ALLOC(ptr, size) ptr == NULL ? malloc(size) : realloc(ptr, size)

#define STR_EQUALS(first, second) strcmp(first, second) == 0

#define PROTOCOL_HTTP "http"
#define PROTOCOL_HTTPS "https"
#define GET_AFTER_PROTOCOL(url) strstr(url, "://")

#define DEFAULT_PROTOCOL PROTOCOL_HTTP

#define HTTP_VERSION "1.1"
#define HTTP_DEFAULT_PORT 80
#define HTTPS_DEFAULT_PORT 443

#define COLOR_FONT_BLACK "30"
#define COLOR_FONT_RED "31"
#define COLOR_FONT_GREEN "32"
#define COLOR_FONT_YELLOW "33"
#define COLOR_FONT_BLUE "34"

#define COLOR_BACKGROUND_BLACK "30"
#define COLOR_BACKGROUND_RED "31"
#define COLOR_BACKGROUND_GREEN "32"
#define COLOR_BACKGROUND_YELLOW "33"
#define COLOR_BACKGROUND_BLUE "34"

#define FONT_ATTR_CLEAN "0"
#define FONT_ATTR_STRIKE "1"
#define FONT_ATTR_UNDERLINE "4"
#define FONT_ATTR_SHOOT "5"

#define PRINT_STYLE_CLEANER() "\033[0m"
#define PRINT_STYLE_MAKER3(attr, font_color, background_color) "\033["attr";"font_color";"background_color"m"
#define PRINT_STYLE_MAKER2(font_color, background_color) "\033["font_color";"background_color"m"
#define PRINT_STYLE_MAKER(color) "\033["color"m"

//setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));

const char* REQUEST_HEADER = 
"GET %s HTTP/"HTTP_VERSION"\r\n"
"Host: %s\r\n"
"Accept: */*\r\n"
"User-Agent: aa\r\n\r\n";

typedef struct _ResponeLine {
	char* key, *value;
} ResponeLine;

typedef struct _ResponeLineList {
	ResponeLine* data;
	ssize_t len;

	void (*free) (struct _ResponeLineList* list);
} ResponeLineList;

int   create_socket_connect(const char* ip, uint16_t port);
char* host_name_to_ip(const char* host_name);
char* cut_out_http_header(int sockfd);

int   __solve_port(const char* url, const char* after);
char* __solve_protocol(const char* url, const char* after_protocol);
char* __solve_host_name(const char* url, const char* after_protocol);
char* solve_url(const char* url, char** host, int* port);

char* get_request_file_path(const char* url);
char* make_request_header(const char* file, const char* domain);

ResponeLine* responeLine_get_respone(const char* header, char* http_version, int* http_respone_code, char* respone_message, ssize_t* result_size);
void responeLine_free(ResponeLine* ptr, ssize_t size);
void responeLine_add(ResponeLine** ptr, ssize_t* size, const char* key, const char* value);
char* responeLine_to_string(ResponeLine* ptr, ssize_t size);
ResponeLine* responeLine_look_up(ResponeLine* lines, ssize_t size, const char* needle, ssize_t* result_size);

ResponeLineList responeLineList_make(ResponeLine* data, ssize_t size);
void __responeLineList_free(ResponeLineList* source);
void responeLineList_free(ResponeLineList* source);

#define solve_protocol(url) __solve_proto(url, GET_AFTER_PROTOCOL(url))
#define solve_host_name(url) __solve_host_name(url, GET_AFTER_PROTOCOL(url))
#define solve_port(url) __solve_port(url, GET_AFTER_PROTOCOL(url))

#define set_socket_timeout(fd, seconds, ms) \
{\
	struct timeval __timeout = {seconds, ms};\
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&__timeout, sizeof(struct timeval));\
}



int create_socket_connect(const char* ip, uint16_t port) {
	int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in fd_addr;
	memset(&fd_addr, 0, sizeof(fd_addr));
	fd_addr.sin_addr.s_addr = inet_addr(ip);
	fd_addr.sin_family = AF_INET;
	fd_addr.sin_port = htons(port);

	printf("ip: %s, port: %d\n", ip, port);

	if (connect(fd, (struct sockaddr* ) &fd_addr, sizeof(fd_addr)) < 0) {
		PRINTF_ERROR("connect failed\n");
	}
	return fd;
}

char* host_name_to_ip(const char* host_name) {
	struct hostent* ip = gethostbyname(host_name);
	if (ip == NULL) PRINTF_ERROR("DNS 解析错误\n");
	return inet_ntoa(*(struct in_addr* )ip->h_addr_list[0]);
}

#ifdef ENABLE_HTTPS

#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define REQUIRE_SSL_PTR_NOT_NULL(field, msg) __REQUIRE_SSL_RESULT(field, msg, == NULL)

#define __REQUIRE_SSL_RESULT(field, msg, whatIsTrue) {\
if ((field) whatIsTrue) PRINTF_ERROR(msg"\nReason: %s", ERR_reason_error_string(ERR_get_error()));\
}

#define INIT_SSL() {\
SSL_library_init();\
OpenSSL_add_all_algorithms();\
SSL_load_error_strings();\
}

#define CLOSE_SSL() {\
	ERR_free_strings();\
	sk_SSL_COMP_free(SSL_COMP_get_compression_methods());\
	EVP_cleanup();\
}

SSL* create_ssl_connect(SSL_CTX* ctx, int fd) {
	SSL* ssl = SSL_new(ctx);
	REQUIRE_SSL_PTR_NOT_NULL(ssl, "SSL is NULL.");
	__REQUIRE_SSL_RESULT(SSL_set_fd(ssl, fd), "setfd failed!", == 0 /* NULL */);
	__REQUIRE_SSL_RESULT(SSL_connect(ssl), "HTTPS connect failed\n", != 1);
	return ssl;
}

#define close_https_connect(ssl) {\
SSL_shutdown(ssl);SSL_free(ssl);\
}

/** Remember to free */
char* cut_out_https_header(SSL* ssl) {
	char buffer, *header = malloc(1);
	ssize_t len = 1;
	int flag = 0;
	while (SSL_read(ssl, &buffer, 1) > 0) {
		header[len - 1] = buffer;
		if (buffer == '\n' || buffer == '\r') {
			if (++flag == 4) {
				break;
			}
		} else flag = 0;
		header = (char* ) realloc(header, ++len);
	}
	header[len - 1] = 0;
	return header;
}

#endif

/** Remember to free */
char* cut_out_http_header(int sockfd) {
	char buffer, *header = malloc(1);
	ssize_t len = 1;
	bool before_nr = false;
	while (recv(sockfd, &buffer, 1, 0) > 0) {
		header[len - 1] = buffer;
		if (buffer == '\n' && len >= 2 && header[len - 2] == '\r') {
			if (before_nr) {
				break;
			} else before_nr = true;
		} else before_nr = false;
		header = (char* ) realloc(header, ++len);
	}
	header[len - 1] = 0;
	return header;
}



/** Remember to free */
char* __solve_protocol(const char* url, const char* after_protocol) {
	char *protocol = NULL;
	if (after_protocol) {
		for (ssize_t i = 0; i < strlen(url); i++) {
			protocol = protocol ? (char* ) realloc(protocol, i + 2) : calloc(1, 1);
			if (url[i] == ':') break;
		    protocol[i] = url[i];    
		}
	} else {
		protocol = (char* ) calloc(1, strlen(DEFAULT_PROTOCOL) + 1);
		strcpy(protocol, DEFAULT_PROTOCOL);
	}
	return protocol;
}

/** Remember to free */
char* __solve_host_name(const char* url, const char* after_protocol) {

	after_protocol = after_protocol ? after_protocol + 3:url;//去掉前面的协议
	char* hostname = NULL;

	for (ssize_t i = 0; i < strlen(after_protocol); i++) {
		hostname = hostname ? (char* ) realloc(hostname, i + 2) : calloc(1, 1);
		if (after_protocol[i] == '/' || after_protocol[i] == ':') break;
		hostname[i] = after_protocol[i];
	}
	return hostname;
}

int __solve_port(const char* url, const char* after) {
	after = (after)//is not null, has proto
		    ? strstr(after + 3, ":") //去掉前面的协议
		    : strstr(url, ":");

	int result = 0;
	if (after) {
		sscanf(after, ":%d", &result);
	} 
	return result;
}

/** Remember to free */
char* solve_url(const char* url, char** host, int* port) {
	const char* after_proto = GET_AFTER_PROTOCOL(url);

	char *proto = __solve_protocol(url, after_proto);
	int m_port = __solve_port(url, after_proto);
	
	
	if (m_port == 0) {//default
		if (STR_EQUALS(proto, "http")) {
			*port = HTTP_DEFAULT_PORT;
		} else if (STR_EQUALS(proto, "https")) {
			*port = HTTPS_DEFAULT_PORT;
		} else {
			PRINTF_ERROR("Unknow proto %s\n", proto);
		}
	} else *port = m_port;

	*host = __solve_host_name(url, after_proto);

	return proto;
}

/** Do not free */
char* get_request_file_path(const char* url) {
	char* tmp = (tmp = strstr(url, "://")) ? //has proto
					strstr(tmp + 3, "/"):
					strstr(url, "/");
	return tmp ? tmp : "/";
}

/** Remember to free */
char* make_request_header(const char* file, const char* domain) {
	char* result = NULL;
	asprintf(&result, REQUEST_HEADER, file, domain);
	return result;
}

/** Remember to free */
ResponeLine* responeLine_get_respone(const char* header, char* http_version, int* http_respone_code, char* respone_message, ssize_t* result_size) {
	char* dup = strdup(header), *token = strtok(dup, "\r\n");

	ssize_t m_result_size = 1;
	ResponeLine* result = (ResponeLine* ) malloc(sizeof(ResponeLine));

	sscanf(token, "HTTP/%s %d %s", http_version, http_respone_code, respone_message);

	while ((token = strtok(NULL, "\r\n")) != NULL) {
		char *key = NULL, *value = NULL, *proccessing = NULL;
		bool skip = false, keyFinished = false;
		ssize_t proccessingIndex, i;
		for (i = proccessingIndex = 0; i <= strlen(token)/*这里加 = 是为了把最后一个 \0 算进去*/; ++i) {
			if (skip) {
				skip = false;
				continue;
			}
			if (!keyFinished && token[i] == ':') {
				skip =/*下一个是一个空格*/keyFinished = true;
				proccessing[proccessingIndex] = '\0';
				key = proccessing; //key finished
				/** reset proccessing */
				proccessing = NULL;
				proccessingIndex = 0;
			} else {
				proccessing = (char* ) AUTO_ALLOC(proccessing, ++proccessingIndex + 1);
				proccessing[proccessingIndex - 1] = token[i];
			}
		}
		proccessing[proccessingIndex] = '\0';
		value = proccessing;
		/** add into result and realloc result */
		(result + m_result_size - 1)->key = key;
		(result + m_result_size - 1)->value = value;
		result = (ResponeLine*) realloc(result, (++m_result_size) * sizeof(ResponeLine));
	}
	if (result_size != NULL) *result_size = m_result_size - 1;
	free(dup);
	return result;
}

void responeLine_free(ResponeLine* ptr, ssize_t size) {
	for (register ssize_t i = 0; i < size; ++i) {
		free(ptr[i].key);free(ptr[i].value);
	}
	free(ptr);
}

void responeLine_add(ResponeLine** ptr, ssize_t* size, const char* key, const char* value) {
	*ptr = (ResponeLine*) AUTO_ALLOC(*ptr, ++(*size) * sizeof(ResponeLine));
	((*ptr) + (*size) - 1)->key = strdup(key);
	((*ptr) + (*size) - 1)->value = strdup(value);
}

/** Remember to free */
char* responeLine_to_string(ResponeLine* ptr, ssize_t size) {
	char* result = NULL;
	size_t result_len = 3/* \r\n\0 */, avaible_size = 0;
	for (register ssize_t i = 0; i < size; ++i) {
		ssize_t key_size = strlen(ptr[i].key), value_size = strlen(ptr[i].value);
		ssize_t total_size = value_size + key_size + 4/* `\r\n` and `: ` */ ;

		result_len += total_size;
		result = AUTO_ALLOC(result, result_len);
		
		memcpy(result + avaible_size, ptr[i].key, key_size);
		avaible_size += key_size;

		memcpy(result + avaible_size, ": ", 2);
		avaible_size += 2;

		memcpy(result + avaible_size, ptr[i].value, value_size);
		avaible_size += value_size;

		memcpy(result + avaible_size, "\r\n", 2);
		avaible_size += 2;
	}
	memcpy(result + avaible_size, "\r\n\0", 3);
	return result;
}



ResponeLine* responeLine_look_up(ResponeLine* lines, ssize_t size, const char* needle, ssize_t* result_size) {
	ResponeLine* result = NULL;
	ssize_t m_rz = 0;
	for (ssize_t i = 0; i < size; i++) {
		if (STR_EQUALS(lines[i].key, needle)) {
			result = AUTO_ALLOC(result, ++m_rz * sizeof(ResponeLine));
			result[m_rz - 1] = lines[i];
		}
	}
	if (result_size != NULL)
		*result_size = m_rz;
	return result;
}

ResponeLineList responeLineList_look_up(ResponeLineList list, const char* needle) {
	ssize_t result_size;
	ResponeLineList result;

	result.data = responeLine_look_up(list.data, list.len, needle, &result_size);
	result.free = &__responeLineList_free;
	result.len = result_size;
	return result;
}

void responeLineList_free(ResponeLineList* source) {
	responeLine_free(source->data, source->len);
	source->free = NULL; source->data = NULL; source->len = 0;
}

/** 该函数只将指针置零 */
void __responeLineList_free(ResponeLineList* source) {
	source->free = NULL; source->data = NULL; source->len = 0;
}

#define responeLineList_to_string(list) responeLine_to_string(list.data, list.len)
#define responeLineList_add(list, key, value) responeLine_add(&(list.data), &(list.len), key, value)

ResponeLineList responeLineList_get_respone(const char* header, char* http_version, int* http_respone_code, char* respone_message) {
	ssize_t result_size;
	ResponeLineList result;

	result.data = responeLine_get_respone(header, http_version, http_respone_code, respone_message, &result_size);
	result.len = result_size;
	result.free = &responeLineList_free;

	return result;
}

int main(int argc, char *argv[])
{
	int port;
	char *host, *pro = solve_url(argv[1], &host, &port),
		*request_file = get_request_file_path(argv[1]);

	printf("host: %s, port: %d, pro: %s, file:%s\n", host, port, pro, request_file);


	char buffer[1024 * 2];

	int fd = create_socket_connect(host_name_to_ip(host), port);
	set_socket_timeout(fd, 5, 0);
	char* request_header = make_request_header(request_file, host);
	printf("request header: %s\n", request_header);

	char http_version[10], respone_message[20];
	int code;

	ssize_t responeLine_size;

#ifdef ENABLE_HTTPS
	if (STR_EQUALS(pro, "https")) {
		INIT_SSL();
		SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
		REQUIRE_SSL_PTR_NOT_NULL(ctx, "SSL_CTX_new failed.");

		SSL* ssl = create_ssl_connect(ctx, fd);
		SSL_write(ssl, request_header, strlen(request_header));
		printf("recvicing\n");
		char *header = cut_out_https_header(ssl);
		printf("header: %s\n, others\n", header);
		
		ResponeLine* lines = responeLine_get_respone(header, http_version, &code, respone_message, &responeLine_size);

		ssize_t size = 0;
		while ((size = SSL_read(ssl, buffer, sizeof(buffer))) > 0) {
			printf("size: %ld, msg: %s", size, buffer);
			memset(buffer, 0, sizeof(buffer));
		}

		responeLine_add(&lines, &responeLine_size, "XDD", "SHD");

		printf("toString: %s\n", responeLine_to_string(lines, responeLine_size));

		ssize_t result_len;
		ResponeLine* lookup_result = responeLine_look_up(lines, responeLine_size, "Set-Cookie", &result_len);

		printf("len: %ld, value: %s\n", result_len, (lookup_result + 2)->value);

		responeLine_free(lines, responeLine_size);

		free(header);

		close_https_connect(ssl);
		SSL_CTX_free(ctx);

		CLOSE_SSL();

		} else 
#endif 
	{
		send(fd, request_header, strlen(request_header), 0);	

		char *header = cut_out_http_header(fd);
		ResponeLine* lines = responeLine_get_respone(header, http_version, &code, respone_message, &responeLine_size);
		responeLine_free(lines, responeLine_size);
		free(header);

		printf("recvicing\n");
		ssize_t size  = 0;
		while ((size = recv(fd, buffer, sizeof(buffer), 0)) > 0) {
			printf("size: %ld, msg: %s", size, buffer);
			memset(buffer, 0, sizeof(buffer));
		}
	}

	printf("http_version: %s, code: %d, respone_message: %s\n", http_version, code, respone_message);
	close(fd);

	free(host); free(pro); free(request_header);

	return 0;
}
