#ifndef __DDZ_SYS_FUNCS_HPP__
#define __DDZ_SYS_FUNCS_HPP__

#if defined (HAVE_SYS_TYPES) || (defined(__has_include) && __has_include("sys/types.h"))
#include <sys/types.h>
#endif

#include <stdint.h>

namespace ddz::platform {

#ifndef __pid_t_defined
typedef int32_t pid_t;
#endif

pid_t get_pid() noexcept;
pid_t get_tid() noexcept;

}

#endif /* end of include guard: __DDZ_SYS_FUNCS_HPP__ */
