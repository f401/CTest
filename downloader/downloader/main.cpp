#include "netFramework/Socket.hpp"
#include <stdio.h>

char header[] = 
"GET / HTTP/1.1\r\n"
"Host: www.baidu.com\r\n"
"Accept: */*\r\n"
"User-Agent: aa\r\n\r\n";

int main(int argc, char *argv[])
{
	net::Address addr = net::Address::create("www.baidu.com", 80);
	printf("host: %s, port: %d\n", addr.getIP(), addr.getPort());
	net::ClientSocket sock = net::ClientSocket::createConnect(addr);
	net::MutableAllocBuffer_p buff = net::MutableAllocBuffer::create(100);
	net::MutableBuffer_p buff2 = net::MutableBuffer::create(header, strlen(header));
	sock.getFileDesc()->write(buff2->convertToImmutable());
	while(sock.getFileDesc()->read(buff) > 0) {
		printf("%s\n", (const char* )buff->get());
		buff->clear();
	}
	return 0;
}
