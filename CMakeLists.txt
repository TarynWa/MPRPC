cmake_minimum_required(VERSION 3.14)
project(mprpc)

# 动态库输出：嵌入大项目构建时由顶层统一指向 chat/lib；
# 独立构建（autobuild.sh）时输出到本模块 lib/、可执行文件到 bin/
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

    # 独立构建时 nwl / muduo_log 目标不存在，依次引入同级模块；
    # 嵌入大项目构建时它们已由顶层 add_subdirectory 定义（nwl 依赖 muduo_log，顺序不能反）
    if(NOT TARGET muduo_log)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../logsystem
                         ${CMAKE_BINARY_DIR}/logsystem-build)
    endif()
    if(NOT TARGET nwl)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../NetWork
                         ${CMAKE_BINARY_DIR}/network-build)
    endif()
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
