#ifndef __NET_FILE_DESC_HPP__
#define __NET_FILE_DESC_HPP__

extern "C" {
#include <fcntl.h>
#include <unistd.h>
}

#include "Buffer.hpp"
#include "NetDefs.hpp"
#include "PrintUtils.hpp"

namespace net {
class FileDescriptor {
public:
  FileDescriptor(fd_t fd) : fd(fd) {}
  ~FileDescriptor() {
    if (fd != -1) {
      ::close(fd);
    }
  }

  static FileDescriptor openFile(const char *name, int flag, mode_t mode = 0) {
    fd_t fd = ::open(name, flag, mode);
    if (fd == -1)
      utils::printSystemError("Open Error");
    return FileDescriptor(fd);
  }

  ssize_t write(const ImmutableBuffer &buf) const { return write(buf, buf.size()); }

  ssize_t write(const ImmutableBuffer &buf, size_t size) const {
    return ::write(fd, buf.get(), size);
  }

  ssize_t read(MutableBuffer &buf) const { return ::read(fd, buf.get(), buf.size()); }

  fd_t get() const { return fd; }

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
