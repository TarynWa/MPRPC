#pragma once
#include"mprpcconfig.h"
#include <iostream>
#include <unistd.h>
class MprpcApplication
{
    public:
    static void Init(int argc,char** argv);
    static MprpcApplication& GetInstance();
     static MprpcConfig& GetConfig();
    
    private:
    static MprpcConfig m_config;
    MprpcApplication(){}
    //拷贝构造
    MprpcApplication(const MprpcApplication&)=delete;
    //移动构造
    MprpcApplication(MprpcApplication&&)=delete;                                                                                                                                       
};