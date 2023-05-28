#ifndef SOCKET_H
#define SOCKET_H

#include "FileDesc.hpp"
#include "NetAddr.hpp"

extern "C" {
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
}

#include <memory>

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
    if (sock.connect(addr) == -1) {
      utils::printSystemError("Error when connecting.");
    }
    return sock;
  }

  virtual int connect(const Address &addr) {
    struct ::sockaddr_in sock;
    ::memset(&sock, 0, sizeof(sock));
    sock.sin_addr.s_addr = addr.getInternetAddress();
    sock.sin_port = addr.getEndianPort();
    sock.sin_family = AF_INET;

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
    return ServerSocket(::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
  }

  virtual int bind(const Address &addr) const noexcept {
    struct ::sockaddr_in sock;
    ::memset(&sock, 0, sizeof(sock));
    sock.sin_addr.s_addr = addr.getInternetAddress();
    sock.sin_port = addr.getEndianPort();
    sock.sin_family = AF_INET;

    return ::bind(fd->get(), (struct sockaddr *)&sock, sizeof(sock));
  }

  virtual int listen(int maxCount) const noexcept {
    return ::listen(fd->get(), maxCount);
  }

  virtual std::pair<std::unique_ptr<FileDescriptor>, Address>
  acceptWithClientInfo() const noexcept {
    sockaddr_in addr;
    socklen_t size = 16;
    fd_t clientFd = ::accept(fd->get(), (struct sockaddr *)&addr, &size);
    return std::make_pair(
        std::make_unique<FileDescriptor>(clientFd),
        Address::create(inet_ntoa(addr.sin_addr), ::ntohs(addr.sin_port)));
  }

  virtual std::unique_ptr<FileDescriptor> accept() const noexcept {
    return std::make_unique<FileDescriptor>(::accept(fd->get(), NULL, NULL));
  }

protected:
  ServerSocket(int fd) : Socket(fd) {}
};

}; // namespace net

#endif /* end of include guard: SOCKET_H */
