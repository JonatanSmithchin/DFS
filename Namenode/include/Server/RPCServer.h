//
// Created by lxx18 on 2023/8/25.
//

#ifndef NAMENODE_RPCSERVER_H
#define NAMENODE_RPCSERVER_H

#include "../NameSystem/NameSystem.h"
#include "DatanodeServiceImpl.h"
#include "ClientServiceImpl.h"

class RPCServer {
private:
    NameSystem* m_nameSystem;
    ClientServiceImpl* m_clientService;
    DatanodeServiceImpl* m_datanodeService;
public:
    RPCServer(NameSystem *nameSystem, ClientServiceImpl *ClientService, DatanodeServiceImpl *DatanodeService);
    void RunServer();
};


#endif //NAMENODE_RPCSERVER_H
