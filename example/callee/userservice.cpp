#include <iostream>
#include <string>
#include "user.pb.h"
#include"mprpcapplication.h"
#include"rpcprovider.h"
class UserService : public fixbug::UserServiceRpc
{
public:
    // 远程服务器本地的登录函数
    bool Login(std::string name, std::string pwd)
    {

        return  false;
    }
    // 远程服务器本地的注册函数
    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        return true;
    }
    //重写基类中UserService的虚函数 远程调用本地函数的方法
    void Login(::google::protobuf::RpcController *controller,
                       const ::fixbug::LoginRequest *request,
                       ::fixbug::LoginResponse *response,
                       ::google::protobuf::Closure *done){
                    std::string name=request->name();
                    std::string pwd=request->pwd();
                    bool login_result=Login(name,pwd);
                    fixbug::ResultCode*code=response->mutable_result();
                    code->set_errcode(0);
                    code->set_errmsg("");
                    response->set_sucess(login_result);
                    done->Run();
                       }
    void Resgister(::google::protobuf::RpcController *controller,
                           const ::fixbug::RegisterRequest *request,
                           ::fixbug::RegisterResponse *response,
                           ::google::protobuf::Closure *done){

                           }
};
int main(int argc , char** argv)
{
    //调用框架的初始化函数
    MprpcApplication::Init(argc,argv);
   // LOG_INFO<<"MAIN.CPP";
    RpcProvider provider;
    provider.NotifyService(new UserService());
    provider.Run();
    return 0;
}