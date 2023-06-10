cmake_minimum_required(VERSION 3.10)
include(CheckIncludeFile)
include(CheckFunctionExists)
project(DDZ)


set(CMAKE_CXX_FLAGS -Wall)


macro(add_compile_macro defs)
	add_definitions("-D${defs}")
endmacro()

function(checkIncludeAndDefine fileName defineAs)
	check_include_file("${fileName}" "${defineAs}")
	add_compile_macro(${defineAs})
endfunction()

function(checkFunctionAndDefile funcName defineAs) 
	check_function_exists(${funcName} ${defineAs})
	if (${defineAs})
		add_compile_macro("${defineAs}")
	endif()
endfunction()

option(BENCHMARK_BUILD OFF "Run Benchmarks")
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/utils __SRCS)

list(APPEND SRCS ${__SRCS})
include_directories(${PROJECT_SOURCE_DIR}/src/common)

add_executable(main ${SRCS})
if (BENCHMARK_BUILD)
	find_package(benchmark REQUIRED)
	add_compile_macro(BENCHMARK_BUILD)
	list(APPEND SRCS ${PROJECT_SOURCE_DIR}/benchmarks/main.cpp)
	include_directories(APPEND ${benchmark_INCLUDE_DIRS})
	target_link_libraries(main PRIVATE benchmark::benchmark)
endif()

checkFunctionAndDefile(strdup HAVE_STRDUP)
