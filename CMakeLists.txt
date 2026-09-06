cmake_minimum_required(VERSION 3.14)
project(mprpc)

# 动态库输出由顶层 CMAKE_LIBRARY_OUTPUT_DIRECTORY 统一指向 chat/lib
include_directories(${PROJECT_SOURCE_DIR}/example)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(example)
