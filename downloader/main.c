#define ENABLE_HTTPS

#define HTTP_DEFAULT_PORT 80
#define HTTPS_DEFAULT_PORT 443
#define DEFAULT_PROTO "http"

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

//setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));

const char* REQUEST_HEADER = 
"GET /download/e80d9b3bf5085002218d4be59e668bac718abbc6?name=client.jar HTTP/1.1\r\n"
"Host: bmclapi2.bangbang93.com\r\n"
"Accept: */*\r\n"
"User-Agent: aa\r\n\r\n";

int create_connect(const char* ip, uint16_t port) {
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

#endif

#define str_equals(first, second) strcmp(first, second) == 0

char* solve_proto(const char* url) {
	char* after_proto = strstr(url, "://"), *proto = NULL;
	if (after_proto) {
		for (ssize_t i = 0; i < strlen(url); i++) {
			proto = proto ? (char* ) realloc(proto, i + 2) : calloc(1, 1);
			if (url[i] == ':') break;
		    proto[i] = url[i];    
		}
	} else {
		proto = (char* ) calloc(1, strlen(DEFAULT_PROTO) + 1);
		strcpy(proto, DEFAULT_PROTO);
	}
	return proto;
}

char* solve_host_name(const char* url) {
	const char* after_proto = strstr(url, "://");
	after_proto = after_proto ? after_proto + 3:url;//去掉前面的协议
	char* hostname = NULL;
	for (ssize_t i = 0; i < strlen(after_proto); i++) {
		hostname = hostname ? (char* ) realloc(hostname, i + 2) : calloc(1, 1);
		if (after_proto[i] == '/' || after_proto[i] == ':') break;
		hostname[i] = after_proto[i];
	}
	return hostname;
}

int solve_port(const char* url) {
	char* after = (after = strstr(url, "://"))//is not null, has proto
			    ? strstr(after + 3, ":") //去掉前面的协议
			    : strstr(url, ":");

	int result = 0;
	if (after) {
		sscanf(after, ":%d", &result);
	} 
	return result;
}

char* solve_url(const char* url, char** host, int* port) {
	char *proto = solve_proto(url);
	int m_port = solve_port(url);
	
	
	if (m_port == 0) {//default
		if (str_equals(proto, "http")) {
			*port = HTTP_DEFAULT_PORT;
		} else if (str_equals(proto, "https")) {
			*port = HTTPS_DEFAULT_PORT;
		} else {
			PRINTF_ERROR("Unknow proto %s\n", proto);
		}
	} else *port = m_port;

	*host = solve_host_name(url);

	return proto;
}

int main(int argc, char *argv[])
{
	/*char buffer[1024 * 1024 * 2];

	int fd = create_connect(host_name_to_ip("6010f16780d7c5acec1b4134.openbmclapi.933.moe"), 4000);

	INIT_SSL();

	SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
	printf("ctx: %p\n", ctx);
	SSL* ssl = create_https_connect(ctx, fd);

	printf("request header: %s\n", REQUEST_HEADER);
	SSL_write(ssl, REQUEST_HEADER, strlen(REQUEST_HEADER));

	printf("recvicing\n");
	ssize_t size = SSL_read(ssl, buffer, sizeof(buffer) - 1);
	printf("size: %ld, msg: %s", size, buffer);

	size = SSL_read(ssl, buffer, sizeof(buffer) - 1);
	printf("size: %ld, msg: %s", size, buffer);

	close_https_connect(ssl);
	close(fd);
	SSL_CTX_free(ctx);
*/
	char* host;
	int port;
	char* pro = solve_url(argv[1], &host, &port);
	
	printf("host: %s, port: %d, pro: %s\n", host, port, pro);

	return 0;
}
