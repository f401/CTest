#ifndef SOCKET_H
#define SOCKET_H

#include "FileDesc.hpp"
#include "NetAddr.hpp"

extern "C" {
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
}

namespace net {

class Socket {
public:
  FileDescriptor *getFileDesc() { return fd; }
  Socket(int fd) : fd(new FileDescriptor(fd)) {}

  virtual ~Socket() { delete fd; }
  Socket(Socket &&) = default;

protected:
  FileDescriptor *fd = nullptr;
};

class ClientSocket : public Socket {
public:
  static ClientSocket createSocket() {
    return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  }

  static ClientSocket createConnect(const Address &addr) {
    ClientSocket sock = createSocket();
    sock.connect(addr);
    return sock;
  }

  virtual int connect(const Address &addr) {
    struct ::sockaddr_in sock;
    ::memset(&sock, 0, sizeof(sock));
    sock.sin_addr.s_addr = ::inet_addr(addr.getIP());
    sock.sin_family = AF_INET;
    sock.sin_port = ::htons(addr.getPort());

    return ::connect(fd->get(), (struct sockaddr *)&sock, sizeof(sock));
  }

protected:
  ClientSocket(int fd) : Socket(fd) {}
  bool connected = false;
};

}; // namespace net

#endif /* end of include guard: SOCKET_H */
