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
	net::BufferAlloc buff(100);
	sock.getFileDesc()->write(net::Buffer(header, strlen((header))));
	while(sock.getFileDesc()->read(buff) > 0) {
		printf("%s\n", (const char* )buff.get());
		buff.clear();
	}
	return 0;
}
