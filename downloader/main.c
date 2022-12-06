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

#define STR_EQUALS(first, second) strcmp(first, second) == 0

#define PROTOCOL_HTTP "http"
#define PROTOCOL_HTTPS "https"

#define DEFAULT_PROTOCOL PROTOCOL_HTTP

#define HTTP_VERSION "1.1"

#define HTTP_DEFAULT_PORT 80
#define HTTPS_DEFAULT_PORT 443

//setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));

const char* REQUEST_HEADER = 
"GET %s HTTP/"HTTP_VERSION"\r\n"
"Host: %s\r\n"
"Accept: */*\r\n"
"User-Agent: aa\r\n\r\n";

typedef struct _ResponeLine {
	char* key, value;
	struct _ResponeLine* next;
} ResponeLine;

int create_http_connect(const char* ip, uint16_t port) {
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

#define INIT_SSL() {\
SSL_library_init();\
OpenSSL_add_all_algorithms();\
SSL_load_error_strings();\
}

SSL* create_https_connect(SSL_CTX* ctx, int fd) {
	SSL* ssl = SSL_new(ctx);
	SSL_set_fd(ssl, fd);
	if (SSL_connect(ssl) == -1) {
		PRINTF_ERROR("HTTPS connect failed\n");
	}
	return ssl;
}

#define close_https_connect(ssl) {\
SSL_shutdown(ssl);SSL_free(ssl);\
}

char* cut_out_https_header(SSL* ssl) {
	char buffer, *header = (char* ) malloc(1);
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

char* cut_out_http_header(int sockfd) {
	char buffer, *header = (char* ) malloc(1);
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

#define GET_AFTER_PROTOCOL(url) strstr(url, "://")

#define solve_protocol(url) __solve_proto(url, GET_AFTER_PROTOCOL(url))

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

#define solve_host_name(url) __solve_host_name(url, GET_AFTER_PROTOCOL(url))

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

#define solve_port(url) __solve_port(url, GET_AFTER_PROTOCOL(url))

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

char* solve_url(const char* url, char** host, int* port) {
	const char* after_proto = strstr(url, "://");

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

char* get_request_file_path(const char* url) {
	char* tmp = (tmp = strstr(url, "://")) ? //has proto
					strstr(tmp + 3, "/"):
					strstr(url, "/");
	return tmp ? tmp : "/";
}


char* make_request_header(const char* file, const char* domain) {
	char* result = NULL;
	asprintf(&result, REQUEST_HEADER, file, domain);
	return result;
}

ResponeLine* get_respone_data(const char* header, char* http_version, int* http_respone_code, char* respone_message) {
	char* dup = strdup(header);
	
	char* token = strtok(dup, "\r\n");
	sscanf(token, "HTTP/%s %d %s", http_version, http_respone_code, respone_message);

	while ((token = strtok(NULL, "\r\n")) != NULL) {
		//TODO: FINISH
		printf("%s\n", token);

	}

	free(dup);
}

int main(int argc, char *argv[])
{
	int port;
	struct timeval timeout = {5, 10};
	char* host, * pro = solve_url(argv[1], &host, &port),
		*request_file = get_request_file_path(argv[1]);
	printf("host: %s, port: %d, pro: %s, file:%s\n", host, port, pro, request_file);


	char buffer[1024 * 2];

	int fd = create_http_connect(host_name_to_ip(host), port);
	char* request_header = make_request_header(request_file, host);
	printf("request header: %s\n", request_header);

	char http_version[10], respone_message[20];
	int code;


	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
#ifdef ENABLE_HTTPS
	if (STR_EQUALS(pro, "https")) {
		INIT_SSL();
	
		SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
		SSL* ssl = create_https_connect(ctx, fd);
	
		SSL_write(ssl, request_header, strlen(request_header));
	
		printf("recvicing\n");
		char *header = cut_out_https_header(ssl);
		printf("header: %s\n \033[47;31mreal:\033[0m]\n", header);
		
		get_respone_data(header, http_version, &code, respone_message);

		ssize_t size = 0;
		while ((size = SSL_read(ssl, buffer, sizeof(buffer))) > 0) {
			printf("size: %ld, msg: %s", size, buffer);
			memset(buffer, 0, sizeof(buffer));
		}
	
		close_https_connect(ssl);
		SSL_CTX_free(ctx);

		printf("http_version: %s, code: %d, respone_message: %s\n", http_version, code, respone_message);
	} else 
#endif 
	{
		send(fd, request_header, strlen(request_header), 0);	
		printf("recvicing\n");
		ssize_t size  = 0;
		while ((size = recv(fd, buffer, sizeof(buffer), 0)) > 0) {
			printf("size: %ld, msg: %s", size, buffer);
			memset(buffer, 0, sizeof(buffer));
		}
	}
	close(fd);
	return 0;
}
