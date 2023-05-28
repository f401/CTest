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
  static Socket createSocket() {
    return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  }

  FileDescriptor *getFileDesc() { return fd; }
  Socket(int fd) : fd(new FileDescriptor(fd)) {}

  virtual ~Socket() { delete fd; }
  Socket(Socket &&) = default;

protected:
  FileDescriptor *fd = nullptr;
};

class ClientSocket : public Socket {
protected:
  bool connected = false;

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

  void setTimeout(int seconds, int ms) {
    struct timeval __timeout = {seconds, ms};
    setsockopt(fd->get(), SOL_SOCKET, SO_RCVTIMEO, &__timeout,
               sizeof(__timeout));
  }

protected:
  ClientSocket(int fd) : Socket(fd) {}
};

class ServerSocket : public Socket {
public:
  static ServerSocket createSocket() {
    return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  }
protected:
  ServerSocket(int fd) : Socket(fd) {}
};

}; // namespace net

#endif /* end of include guard: SOCKET_H */
