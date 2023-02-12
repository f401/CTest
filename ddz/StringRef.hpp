#ifndef __DDZ_STRING_REF_HPP__

#define __DDZ_STRING_REF_HPP__

#include "defines.hpp"
#include <string>
#include <cstring>

namespace ddz {

class StringRef {
public:
  DDZ_INLINE StringRef(const char *src) : src(src) {}
  DDZ_INLINE StringRef(std::string src) : src(src.c_str()) {}
  DDZ_INLINE StringRef() : src("") {}
  DDZ_INLINE const char *str() const noexcept { return src; };
  DDZ_INLINE char *str() noexcept { return const_cast<char *>(src); }
  DDZ_INLINE std::string cppStr() const noexcept { return std::string(src); }

  bool operator<(const StringRef &other) const noexcept {
    return src < other.src; // compare memory
  }

  bool operator==(const StringRef &other) const noexcept {
	  return other.src == src || strcmp(other.src, src) == 0;
  }

private:
  const char *src;
};

} // namespace ddz

#endif /* end of include guard: __DDZ_STRING_REF_HPP__ */
