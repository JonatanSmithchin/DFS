//
// Created by lxx18 on 2023/9/10.
//

#ifndef DATANODE_RPCSERVER_H
#define DATANODE_RPCSERVER_H

#include "ClientDatanodeServiceImpl.h"
class RPCServer {
private:
    ClientDatanodeServiceImpl* m_clientService;
public:
    RPCServer(ClientDatanodeServiceImpl *clientDatanodeService);
    void RunServer();
};




#endif //DATANODE_RPCSERVER_H
