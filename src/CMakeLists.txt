set(SRC_LIST
    mprpcapplication.cpp
    mprpcconfig.cpp
    rpcprovider.cpp
    zookeeperutil.cpp
    rpcheader.pb.cc)

# 模块内部自带的 logsys（与 src/logsystem 同源）直接编入 libmprpc.so
file(GLOB LOGSYS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../logsys/src/*.cpp)
list(APPEND SRC_LIST ${LOGSYS_SOURCES})

add_library(mprpc SHARED ${SRC_LIST})

# zookeeper_mt 的同步 API 声明在 #ifdef THREADED 内，需定义该宏（PUBLIC 传递给 example）
target_compile_definitions(mprpc PUBLIC THREADED)

target_include_directories(mprpc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../logsys/include
)

find_package(Threads REQUIRED)

# 使用 third_party 下 -fPIC 编译的 muduo（系统 /usr/local 的非 PIC 版无法链入动态库）
set(MUDUO_PIC_ROOT ${CMAKE_SOURCE_DIR}/third_party/muduo-pic)
target_include_directories(mprpc SYSTEM PUBLIC ${MUDUO_PIC_ROOT}/include)
target_link_libraries(mprpc
    PUBLIC
        ${MUDUO_PIC_ROOT}/lib/libmuduo_net.a
        ${MUDUO_PIC_ROOT}/lib/libmuduo_base.a
        protobuf
        zookeeper_mt
        Threads::Threads
)
