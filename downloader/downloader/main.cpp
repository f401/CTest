#include "http/URL.hpp"
#include "http/HttpRequest.hpp"
#include "netFramework/Socket.hpp"
#include <stdio.h>

char header[] = "GET / HTTP/1.1\r\n"
                "Host: www.baidu.com\r\n"
                "Accept: */*\r\n"
                "User-Agent: aa\r\n\r\n";

void __attribute__((unused)) client_test() {
  net::Address_p addr = net::Address::create("www.baidu.com", 80);
  printf("host: %s, port: %d\n", addr->getIP(), addr->getPort());
  net::ClientSocket sock = net::ClientSocket::createConnect(addr);
  net::MutableAllocBuffer_p buff = net::MutableAllocBuffer::create(100);
  net::MutableBuffer_p buff2 =
      net::MutableBuffer::create(header, strlen(header));
  sock.getFileDesc()->write(buff2->convertToImmutable());
  while (sock.getFileDesc()->read(buff) > 0) {
    printf("%s\n", (const char *)buff->get());
    buff->clear();
  }
}

void __attribute__((unused)) server_test() {
  net::Address_p addr = net::AddrInetAny::create(8080);
  net::ServerSocket ss = net::ServerSocket::createSocket();
  ss.bind(addr);
  ss.listen(20);
  for (;;) {
    auto a = ss.accept();
    a->write(*net::ImmutableBuffer::create("hello", 5));
    printf("recv connection\n");
  }
}

void __attribute__((unused)) url_test() {
  net::utils::URL url("https://www.baidu.com/");
  net::http::HttpRequest request = net::http::HttpRequest::create(url);
  printf("%s\n", (char* )request.build()->get());
}

int main(int argc, char *argv[]) {
  url_test();
  return 0;
}
