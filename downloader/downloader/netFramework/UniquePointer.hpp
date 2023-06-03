#ifndef __NET_UNIQUE_PTR__
#define __NET_UNIQUE_PTR__

#include <memory>

namespace net::utils {

template <typename T> class UniquePointer : public std::unique_ptr<T> {
public:
  using std::unique_ptr<T>::unique_ptr;

  UniquePointer<T>(T *ptr) : std::unique_ptr<T>(ptr) {}
  UniquePointer<T>(T &ptr) : std::unique_ptr<T>(&ptr) {}

  template <class U> operator U *() { return this->get(); }

  template <class U> operator U &() { return *this->get(); }
};

} // namespace net::utils

#endif /* end of include guard: __NET_UNIQUE_PTR__  */
