#ifndef __NET_FILE_DESC_HPP__
#define __NET_FILE_DESC_HPP__

extern "C" {
#include <unistd.h>
}

#include "Buffer.hpp"
#include "NetDefs.hpp"

namespace net {
class FileDescriptor final {
public:
  FileDescriptor(fd_t fd) : fd(fd) {}
  ~FileDescriptor() {
    if (fd != -1) {
      ::close(fd);
    }
  }

  ssize_t write(Buffer &buf) const {
    return ::write(fd, buf.get(), buf.size());
  }

  ssize_t read(Buffer &buf) const { return ::read(fd, buf.get(), buf.size()); }

  FileDescriptor(const FileDescriptor &) = delete;
  FileDescriptor &operator=(const FileDescriptor &) = delete;

  FileDescriptor(FileDescriptor &&other) : fd(other.fd) { other.fd = -1; }

  FileDescriptor &operator=(FileDescriptor &&other) {
    fd = other.fd;
    other.fd = -1;
    return *this;
  }

private:
  fd_t fd = -1;
};
} // namespace net

#endif /* end of include guard: __NET_FILE_DESC_HPP__ */
