#include "rpcprovider.h"
#include"mprpcapplication.h"
#include<muduo/net/TcpServer.h>
#include"zookeeperutil.h"
void RpcProvider::NotifyService(::google::protobuf::Service *service)
{
    ServiceInfo service_info;
    //获取对象的服务器信息
    const google::protobuf::ServiceDescriptor*pserviceDesc=service->GetDescriptor();
    std::string  service_name=pserviceDesc->name();
    int methodCnt=pserviceDesc->method_count();
    for(int i=0;i<methodCnt;i++){
        const google::protobuf::MethodDescriptor*pmethodDesc=pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.m_methodMap.insert({method_name, pmethodDesc});
    }
    service_info.m_service = service;
    m_serviceMap.insert({service_name, service_info});
}

void RpcProvider::Run()
{
    std::string ip=MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    muduo::net::InetAddress address(ip, port);
    muduo::net::TcpServer server(&loop, address, "RpcProvider");
    server.setConnectionCallback(std::bind(&onConnection, this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    server.setThreadNum(4);
    //zookeeper的部署
    ZkClient zkCli;
    zkCli.Start();
    // service_name为永久性节点    method_name为临时性节点
    for (auto &sp : m_serviceMap) 
    {
        // /service_name   /UserServiceRpc
        std::string service_path = "/" + sp.first;
        zkCli.Create(service_path.c_str(), nullptr, 0);
        for (auto &mp : sp.second.m_methodMap)
        {
            // /service_name/method_name   /UserServiceRpc/Login 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data, "%s:%d", ip.c_str(), port);
            // ZOO_EPHEMERAL表示znode是一个临时性节点
            zkCli.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);
        }
    }

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port << std::endl;
    server.start();
    loop.loop();
}

void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp)
{
    
}

void RpcProvider::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    if(!conn->connected()){
        conn->shutdown();
    }
}

