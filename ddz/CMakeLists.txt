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

check_function_exists(strdup HAVE_STRDUP)

add_executable(main ${SRCS} ${PLAT_SRCS})
