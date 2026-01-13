#include "zookeeperutil.h"

ZkClient::ZkClient():m_zhandle(nullptr)
{
}

ZkClient::~ZkClient()
{
    if(m_zhandle!=nullptr){
        zookeeper_close(m_zhandle);
    }
}

void ZkClient::Start()
{
    
}
