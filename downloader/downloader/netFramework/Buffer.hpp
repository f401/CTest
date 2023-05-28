#ifndef __NET_FW_BUFFER_HPP__
#define __NET_FW_BUFFER_HPP__ 1

#include "NetDefs.hpp"
#include <cstdlib>
#include <cstring>
#include <exception>
#include <type_traits>

namespace net {

template <class T>
inline constexpr bool not_has_const = std::is_same_v<T, std::remove_const_t<T>>;

template <class T> class Buffer {
protected:
  T *target = nullptr;
  size_t len = 0;

public:
  Buffer(T *buf, size_t len) noexcept : target(buf), len(len) {}
  virtual ~Buffer() noexcept {}

  T *get() noexcept { return this->target; }
  size_t size() noexcept { return this->len; }

  const T *get() const noexcept { return this->target; }
  const size_t size() const noexcept { return this->len; }

  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) noexcept = default;

  virtual Buffer &operator=(const Buffer &) = delete;
  virtual Buffer &operator=(Buffer &&) noexcept = default;

  template <typename Immu = Buffer<const T>>
  std::enable_if_t<not_has_const<T>, Immu>
  convertToImmutable() const {
    return Buffer<const T>(this->target, this->len);
  }

  void clear() noexcept { ::memset(this->target, 0, this->len); }
};

template <class T> class AllocBuffer : public Buffer<T> {
private:
  using Buffer<T>::Buffer;
  static void *copyData(const AllocBuffer &buf) noexcept {
    void *n = ::calloc(0, buf.len);
    ::memmove(n, buf.target, buf.len);
    return n;
  }

public:
  AllocBuffer(size_t len) noexcept : Buffer<T>(::calloc(len, 1), len) {}

  AllocBuffer(const AllocBuffer<T> &other) noexcept {
    Buffer(copyData(other), other.len);
  }

  template <typename Immu = AllocBuffer<const T>>
  std::enable_if_t<not_has_const<T>, Immu>
  convertToImmutable() const {
    return AllocBuffer<const T>(this->target, this->len);
  }

  virtual AllocBuffer &operator=(const AllocBuffer &other) noexcept {
    if (this != &other) {
      this->~AllocBuffer();
      this->target = copyData(other);
      this->len = other.len;
    }
    return *this;
  }

  virtual ~AllocBuffer() noexcept override {
    if constexpr (std::is_same_v<T, std::remove_const_t<T>>) {
      if (this->target != nullptr)
        free(this->target);
    }
  }
};

using ImmutableBuffer = Buffer<const void>;
using MutableBuffer = Buffer<void>;

using ImmutableAllocBuffer = AllocBuffer<const void>;
using MutableAllocBuffer = AllocBuffer<void>;
} // namespace net

#endif /* end of include guard: __NET_FW_BUFFER_HPP__ */
