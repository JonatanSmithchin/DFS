//
// Created by lxx18 on 2023/9/10.
//

#ifndef DATANODE_RPCSERVER_H
#define DATANODE_RPCSERVER_H

#include "ClientDatanodeServiceImpl.h"
#include "DatanodeServiceImpl.h"

class RPCServer {
private:
    ClientDatanodeServiceImpl* m_clientService;
    DatanodeServiceImpl* m_datanodeService;
public:
    RPCServer(ClientDatanodeServiceImpl *clientDatanodeService,DatanodeServiceImpl *datanodeService);
    void RunServer();
};




#endif //DATANODE_RPCSERVER_H
