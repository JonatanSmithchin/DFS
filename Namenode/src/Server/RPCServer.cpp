//
// Created by lxx18 on 2023/8/25.
//

#include "grpcpp/grpcpp.h"
#include "glog/logging.h"
#include "Server/RPCServer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

RPCServer::RPCServer(NameSystem *nameSystem, ClientServiceImpl *ClientService, DatanodeServiceImpl *DatanodeService):

    m_nameSystem(nameSystem),m_clientService(ClientService),m_datanodeService(DatanodeService) {

}

void RPCServer::RunServer() {
    std::string server_address("[::]:8500");

    ServerBuilder builder;

    builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());

    builder.RegisterService(m_datanodeService);
    builder.RegisterService(m_clientService);


    auto server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on "<< server_address;

    server->Wait();
}
