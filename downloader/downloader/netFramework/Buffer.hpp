#ifndef __NET_FW_BUFFER_HPP__
#define __NET_FW_BUFFER_HPP__ 1

#include "NetDefs.hpp"
#include <cstdlib>
#include <cstring>

namespace net {
class Buffer {
public:
  Buffer(void *buf, size_t len) : target(buf), len(len) {}

  virtual ~Buffer() {}

  void *get() { return target; }
  size_t size() { return len; }

  const void *get() const { return target; }
  const size_t size() const { return len; }

  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) = default;

  virtual Buffer &operator=(const Buffer &) = delete;
  virtual Buffer &operator=(Buffer &&) = default;

protected:
  Buffer() {}
  void *target = nullptr;
  size_t len = 0;
};

class BufferAlloc : public Buffer {
public:
  BufferAlloc(size_t len) : Buffer(::calloc(len, 1), len) {}

  BufferAlloc(const BufferAlloc &other) {
    void *target = ::calloc(other.len, 1);
    ::memmove(target, other.target, other.len);
    Buffer(target, other.len);
  }

  virtual BufferAlloc &operator=(const BufferAlloc &other) {
    if (this != &other) {
      this->~BufferAlloc();
      void *target = ::calloc(other.len, 1);
      ::memmove(target, other.target, other.len);

      this->target = target;
      this->len = other.len;
    }
    return *this;
  }

  virtual ~BufferAlloc() override {
    if (target != nullptr)
      free(target);
  }
};
} // namespace net

#endif /* end of include guard: __NET_FW_BUFFER_HPP__ */
