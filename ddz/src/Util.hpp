#ifndef __DDZ_UTIL_HPP__
#define __DDZ_UTIL_HPP__

#include "StringRef.hpp"

namespace ddz::util {

::ddz::StringRef getTimeAsString() noexcept;

::ddz::StringRef concatString(const char *data1, const char *data2,
                              size_t data1Len, size_t data2Len) noexcept;

DDZ_INLINE ::ddz::StringRef concatString(const char *data1, const char *data2) noexcept {
  return concatString(data1, data2, ::strlen(data1), ::strlen(data2));
}

} // namespace ddz::util

#endif /* end of include guard: __DDZ_UTIL_HPP__ */
