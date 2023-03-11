#ifndef __DDZ_STRING_REF_HPP__

#define __DDZ_STRING_REF_HPP__

#include "defines.hpp"
#include <cstring>
#include <ostream>
#include <string>

namespace ddz {

class StringRef {
public:
  DDZ_INLINE StringRef(const char *src, bool free) noexcept
      : src(src), free(free) {}

  DDZ_INLINE StringRef(const char *src) noexcept : StringRef(src, false) {}

  DDZ_INLINE StringRef(std::string src) noexcept : StringRef(src.c_str()) {}

  DDZ_INLINE const char *str() const noexcept { return src; };
  DDZ_INLINE std::string cppStr() const noexcept { return std::string(src); }
  DDZ_INLINE StringRef dup() const noexcept {
    return StringRef(::strdup(src), true);
  }

  DDZ_INLINE bool operator<(const StringRef &other) const noexcept {
    return src < other.src; // compare memory
  }

  DDZ_INLINE bool operator==(const StringRef &other) const noexcept {
    return other.src == src || strcmp(other.src, src) == 0;
  }

  DDZ_INLINE StringRef(const StringRef &ref) noexcept : free(ref.free) {
    if (ref.free) {
      src = strdup(ref.src);
    }
  }

  DDZ_INLINE StringRef(StringRef &&ref) noexcept
      : src(ref.src), free(ref.free) {
    ref.free = false;
    ref.src = nullptr;
  }

  StringRef &operator=(const StringRef &ref) noexcept {
    this->~StringRef();

    free = ref.free;
    src = ref.free ? strdup(ref.src) : ref.src;

    return *this;
  }

  StringRef &operator=(StringRef &&ref) noexcept {
    this->~StringRef();
     
    //move `ref` to `this`
    free = ref.free;
    src = ref.src;

    //set ref to '0'
    ref.free = false;
    ref.src = nullptr;

    return *this;
  } 

  DDZ_INLINE ~StringRef() {
    if (free) {
      delete src;
    }
  }

  DDZ_INLINE friend std::ostream &operator<<(std::ostream &src,
                                             const StringRef &other) noexcept {
    src << other.src;
    return src;
  }

private:
  const char *src;
  bool free;
};

} // namespace ddz

#endif /* end of include guard: __DDZ_STRING_REF_HPP__ */
