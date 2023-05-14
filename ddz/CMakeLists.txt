cmake_minimum_required(VERSION 3.10)
include(CheckIncludeFile)
include(CheckFunctionExists)
project(DDZ)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/common SRCS)

macro(add_compile_macro defs)
	add_definitions("-D${defs}")
endmacro()


function(checkAndDefine fileName defineAs)
	check_include_file("${fileName}" "${defineAs}")
	add_compile_macro(${defineAs})
endfunction()

if (UNIX) 
	checkAndDefine("unistd.h" HAVE_UNISTD)
	checkAndDefine("sys/types.h" HAVE_SYS_TYPES)
	checkAndDefine("sys/syscall.h" HAVE_SYS_SYSCALL)

	check_function_exists(gettid HAVE_GETTID)
	check_function_exists(syscall HAVE_SYSCALL)

	if (HAVE_GETTID) 
		add_compile_macro(DDZ_USE_GLIBC_GETTID)
	elseif(NOT HAVE_SYSCALL)
		message(FATAL_ERROR "Do not have `gettid` or `syscall`")
	endif()

	aux_source_directory(${PROJECT_SOURCE_DIR}/src/platform/unix PLAT_SRCS)
endif()

check_function_exists(strdup HAVE_STRDUP)

add_executable(main ${SRCS} ${PLAT_SRCS})
