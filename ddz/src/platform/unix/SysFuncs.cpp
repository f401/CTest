#include "../SysFuncs.hpp"
#include "../../defines.hpp"

extern "C" {
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
}

using namespace ddz;

pid_t platform::get_pid() noexcept { return ::getpid(); }
pid_t platform::get_tid() noexcept { 
#ifdef DDZ_USE_GLIBC_GET_TID
	return ::gettid();
#else
	return ::syscall(SYS_gettid); 
#endif
}
