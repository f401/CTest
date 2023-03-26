#ifndef __DDZ_STRING_REF_HPP__

#define __DDZ_STRING_REF_HPP__

#include "defines.hpp"
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

namespace ddz {

/// StringRef - 该类负责代理一个指向目标字符串的指针，并提供一些辅助方法.
/// 该指针不能为空
///
/// 该类没有字符串的管理权，也就是不会进行 `new/delete` 等操作
class StringRef {
public:
  StringRef() = default;
  StringRef(std::nullptr_t) = delete;

  constexpr StringRef(const char *str) noexcept
      : src(str), len(std::char_traits<char>::length(str)) {}

  constexpr StringRef(const char *str, size_t sz) noexcept
      : src(str), len(sz) {}

  StringRef(const std::string &src) noexcept
      : src(src.data()), len(src.size()) {}

  /// 返回所代理的指针
  DDZ_NO_DISCARD DDZ_INLINE const char *data() const noexcept { return src; }

  /// 返回std::string版本的代理对象
  DDZ_NO_DISCARD DDZ_INLINE std::string cppStr() const noexcept {
    return std::string(src);
  }

  /// 对于 `compareMem` 的简单封装
  DDZ_NO_DISCARD constexpr int compare(const StringRef &left) const noexcept {
    if (int result = compareMem(left.src, src, std::min(left.len, len))) {
      return result < 0 ? -1 : 1;
    }
    if (len == left.len) {
      return true;
    }
    return len < left.len ? -1 : 1;
  }

  /**
   * operators
   */

  DDZ_NO_DISCARD DDZ_INLINE bool constexpr
  operator<(const StringRef &other) const noexcept {
    return compare(other) < 0;
  }

  DDZ_NO_DISCARD DDZ_INLINE bool constexpr
  operator==(const StringRef &other) const noexcept {
    return other.src == src || compare(other) == 0;
  }

  friend std::ostream &operator<<(std::ostream &src, const StringRef &ref) {
    src << ref.src;
    return src;
  }

private:
  /// 对于memcmp的封装，所有该类重载的操作符最终都会调用该函数
  DDZ_NO_DISCARD_INLINE_CONSTEXPR static int
  compareMem(const char *left, const char *right, size_t size) {
    if (size == 0) {
      return 0;
    }
    return ::memcmp(left, right, size);
  }

  ///指向代理对象的源指针以及字符串长度
  const char *src = nullptr;
  const size_t len = 0;
};

} // namespace ddz

#endif /* end of include guard: __DDZ_STRING_REF_HPP__ */
