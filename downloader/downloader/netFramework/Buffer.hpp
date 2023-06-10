#ifndef __NET_FW_BUFFER_HPP__
#define __NET_FW_BUFFER_HPP__ 1

#include "NetDefs.hpp"
#include "UniquePointer.hpp"
#include <cstdlib>
#include <cstring>
#include <exception>
#include <type_traits>

namespace net {

template <typename T1, typename U> struct __Buffer_Convert_Helper {
  typedef U type;
};

template <typename T1, typename U> struct __Buffer_Convert_Helper<const T1, U> {
  typedef void type;
};

template <class T> class Buffer {
protected:
  T *target = nullptr;
  size_t len = 0;

  typedef
      typename __Buffer_Convert_Helper<T, Buffer<const T> &>::type ImmutableType_t;

public:
  Buffer(T *buf, size_t len) noexcept : target(buf), len(len) {}

  static Buffer<T>* create(T *buff, size_t len) {
	  return new Buffer<T>(buff, len);
  }

  virtual ~Buffer() noexcept {}

  T *get() noexcept { return this->target; }
  size_t size() noexcept { return this->len; }

  const T *get() const noexcept { return this->target; }
  size_t size() const noexcept { return this->len; }

  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) noexcept = default;

  Buffer &operator=(const Buffer &) = delete;
  Buffer &operator=(Buffer &&) noexcept = default;

  virtual ImmutableType_t convertToImmutable() const noexcept {
    if constexpr (!std::is_same_v<ImmutableType_t, void>) {
      return *new Buffer<const T>(this->target, this->len);
    }
  }

  void clear() noexcept { ::memset(this->target, 0, this->len); }
};


template <class T> class AllocBuffer : public Buffer<T> {
private:
  using Buffer<T>::Buffer;
  static void *copyData(const AllocBuffer &buf) noexcept {
    if constexpr (!std::is_const_v<T>) {
      void *n = ::calloc(0, buf.len);
      ::memmove(n, buf.target, buf.len);
      return n;
    } else {
      return const_cast<void *>(buf.target);
    }
  }

  typedef typename __Buffer_Convert_Helper<T, AllocBuffer<const T> &>::type
      ImmutableType_t;

public:
  AllocBuffer(size_t len) noexcept : Buffer<T>(::calloc(len, 1), len) {}

  static AllocBuffer<T>* create(size_t len) noexcept {
	  return new AllocBuffer<T>(len);
  }

  AllocBuffer(const AllocBuffer<T> &other) noexcept {
    Buffer(copyData(other), other.len);
  }

  virtual ImmutableType_t convertToImmutable() const noexcept override {
    if constexpr (!std::is_same_v<void, ImmutableType_t>) {
      return *new AllocBuffer<const T>(this->target, this->len);
    }
  }

  AllocBuffer &operator=(const AllocBuffer &other) noexcept {
    if (this != &other) {
      this->~AllocBuffer();
      this->target = copyData(other);
      this->len = other.len;
    }
    return *this;
  }

  virtual ~AllocBuffer() noexcept override {
    if constexpr (!std::is_const_v<T>) {
      if (this->target != nullptr)
        free(this->target);
    }
  }
};

typedef Buffer<const void> ImmutableBuffer;
typedef Buffer<void> MutableBuffer;
typedef AllocBuffer<const void> ImmutableAllocBuffer;
typedef AllocBuffer<void> MutableAllocBuffer;

typedef utils::UniquePointer<Buffer<const void>> ImmutableBuffer_p;
typedef utils::UniquePointer<Buffer<void>> MutableBuffer_p;
typedef utils::UniquePointer<AllocBuffer<const void>> ImmutableAllocBuffer_p;
typedef utils::UniquePointer<AllocBuffer<void>> MutableAllocBuffer_p;
} // namespace net

#endif /* end of include guard: __NET_FW_BUFFER_HPP__ */
