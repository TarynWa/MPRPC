set(SRC_LIST
    mprpcapplication.cpp
    mprpcconfig.cpp
    rpcprovider.cpp
    zookeeperutil.cpp
    rpcheader.pb.cc)

add_library(mprpc SHARED ${SRC_LIST})

# zookeeper_mt 的同步 API 声明在 #ifdef THREADED 内，需定义该宏
target_compile_definitions(mprpc PUBLIC THREADED)

target_include_directories(mprpc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

find_package(Threads REQUIRED)

# 网络层采用自研 nwl 网络库（libnwl.so，由 src/NetWork 定义）；
# nwl 以 PUBLIC 方式传递 Threads 与日志库 muduo_log 依赖
target_link_libraries(mprpc
    PUBLIC
        nwl
        protobuf
        zookeeper_mt
        Threads::Threads
)
add_library(lib::mprpc ALIAS mprpc)