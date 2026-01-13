set(SRC_LIST 
    mprpcapplication.cpp 
    mprpcconfig.cpp )
add_library(mprpc ${SRC_LIST})
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)