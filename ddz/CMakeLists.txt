cmake_minimum_required(VERSION 3.10)

project(DDZ)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)
add_executable(main ${SRCS})
