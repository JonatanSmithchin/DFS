//
// Created by lxx18 on 2023/9/10.
//

#include <yaml-cpp/yaml.h>
#include "grpcpp/grpcpp.h"
#include "glog/logging.h"
#include "Server/RPCServer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

RPCServer::RPCServer(ClientDatanodeServiceImpl *clientDatanodeService,
                     DatanodeServiceImpl *datanodeService)
                     :m_clientService(clientDatanodeService),m_datanodeService(datanodeService) {

}

void RPCServer::RunServer(){
    YAML::Node node = YAML::LoadFile("../configs/DatanodeConfig.yaml");
    int SERVER_PORT = node["server_port"].as<int>();
    int IPC_PORT = node["ipc_port"].as<int>();

    std::string server_address = "[::]:" + std::to_string(SERVER_PORT);
    std::string ipc_address = "[::]:" + std::to_string(IPC_PORT);

    ServerBuilder builder;

    builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());
    builder.AddListeningPort(ipc_address,grpc::InsecureServerCredentials());

    builder.RegisterService(m_clientService);
    builder.RegisterService(m_datanodeService);

    auto server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on " << server_address;

    server->Wait();
}
