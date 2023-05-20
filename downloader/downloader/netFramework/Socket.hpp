#ifndef SOCKET_H
#define SOCKET_H

#include "NetAddr.hpp"

extern "C" {
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
}

namespace net {
class Socket {
public:
  static Socket createSocket() {
    return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  }
  
  static Socket createConnect(const Address &addr) {
    Socket sock = createSocket();
    sock.connect(addr);
    return sock;
  }

  virtual int connect(const Address &addr) {
    struct ::sockaddr_in sock;
    ::memset(&sock, 0, sizeof(sock));
    sock.sin_addr.s_addr = ::inet_addr(addr.getIP());
    sock.sin_family = AF_INET;
    sock.sin_port = ::htons(addr.getPort());

    return ::connect(fd, (struct sockaddr *)&sock, sizeof(sock));
  }

protected:
  Socket(int fd) : fd(fd) {}
  int fd = -1;
  bool connected = false;
};

}; // namespace downloader

#endif /* end of include guard: SOCKET_H */
