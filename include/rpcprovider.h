#pragma once
#include"google/protobuf/service.h"
#include<nwl/EventLoop.hpp>
#include<nwl/TcpServer.hpp>
#include<string.h>
#include<functional>
#include<google/protobuf/descriptor.h>
#include<unordered_map>

class RpcProvider
{
    public:
    void NotifyService(::google::protobuf::Service* service);
    void Run();
    private:
    nwl::EventLoop loop;
    //处理上报的消息回调函数
    void onMessage(const nwl::TcpConnPtr&, nwl::Buffer*, nwl::Timestamp);
    //处理上报的连接函数
    void onConnection(const nwl::TcpConnPtr&);
    void SendRpcResponse(const nwl::TcpConnPtr&, google::protobuf::Message*);
    // service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap; // 保存服务方法
    };
    // 存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;
};