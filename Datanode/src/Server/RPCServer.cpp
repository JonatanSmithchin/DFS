//
// Created by lxx18 on 2023/9/10.
//

#include "grpcpp/grpcpp.h"
#include "glog/logging.h"
#include "Server/RPCServer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

RPCServer::RPCServer(ClientDatanodeServiceImpl *clientDatanodeService):m_clientService(clientDatanodeService) {

}

void RPCServer::RunServer(){
    std::string server_address("[::]:8501");

    ServerBuilder builder;

    builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());

    builder.RegisterService(m_clientService);

    auto server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on " << server_address;

    server->Wait();
}
