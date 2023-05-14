#include "PrintUtils.hpp"
#include <cstdarg>
#include <cstdio>

namespace downloader::utils {
void __attribute__((format(printf, 1, 2))) printError(const char *src, ...) {
  va_list list;
  va_start(list, src);
  vfprintf(stderr, src, list);
  va_end(list);
}

void printSystemError(const char *src) { perror(src); }
} // namespace downloader::utils
