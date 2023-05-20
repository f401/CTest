#ifndef PRINT_UTILS_HPP
#define PRINT_UTILS_HPP

namespace net::utils
{
///向标准错误流输出
void printError(const char*, ...) __attribute__((format(printf, 1, 2)));

///输出系统调用后出现的错误（perror）
void printSystemError(const char* );
}

#endif /* end of include guard: BASICFUNCTIONS_H */
