#define ENABLE_HTTPS

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
"GET /version/1.7.10/client.jar HTTP/1.1\r\n"
"Host: bmclapi2.bangbang93.com\r\n"
"Accept: */*\r\n"
"User-Agent: aa\r\n\r\n";

int create_connect(const char* ip, uint16_t port) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);

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

#define SSL_INIT() {\
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

int main(int argc, char *argv[])
{
	struct timeval timeout = {5, 0};
	int fd = create_connect(host_name_to_ip("bmclapi2.bangbang93.com"), 80);
	char buffer[1024 * 1024];
	memset(buffer, 0, 1024 * 1024);
	printf("request header: %s\n", REQUEST_HEADER);
	send(fd, REQUEST_HEADER, strlen(REQUEST_HEADER), 0);
	printf("recvicing\n");
	ssize_t size = recv(fd, buffer, sizeof(buffer) - 1, 0);

	printf("size: %ld, msg: %s", size, buffer);
	
	close(fd);


	return 0;
}
