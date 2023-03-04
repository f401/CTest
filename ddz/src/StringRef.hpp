#ifndef __DDZ_STRING_REF_HPP__

#define __DDZ_STRING_REF_HPP__

#include "defines.hpp"
#include <cstring>
#include <ostream>
#include <string>

namespace ddz {

class StringRef {
public:
  DDZ_INLINE StringRef(const char *src) noexcept : src(src) {}
  DDZ_INLINE StringRef(std::string src) noexcept : src(src.c_str()) {}
  DDZ_INLINE StringRef() noexcept : src("") {}
  DDZ_INLINE const char *str() const noexcept { return src; };
  DDZ_INLINE std::string cppStr() const noexcept { return std::string(src); }

  DDZ_INLINE bool operator<(const StringRef &other) const noexcept {
    return src < other.src; // compare memory
  }

  DDZ_INLINE bool operator==(const StringRef &other) const noexcept {
    return other.src == src || strcmp(other.src, src) == 0;
  }

  DDZ_INLINE friend std::ostream &operator<<(std::ostream &src,
                                             const StringRef &other) {
    src << other.src;
    return src;
  }

private:
  const char *src;
};

} // namespace ddz

#endif /* end of include guard: __DDZ_STRING_REF_HPP__ */
