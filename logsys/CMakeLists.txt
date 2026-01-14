


# logsys/CMakeLists.txt（子模块的CMake配置）
# 1. 配置logsys自身的头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 2. 编译logsys的源文件（假设logsys是一个库）
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src LOGSYS_SRCS)
add_library(logsys ${LOGSYS_SRCS})

# 3. （可选）将logsys的include目录暴露给依赖它的模块
target_include_directories(logsys PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)  