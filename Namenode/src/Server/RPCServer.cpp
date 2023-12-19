//
// Created by lxx18 on 2023/8/25.
//

#include <yaml-cpp/yaml.h>
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
    YAML::Node node = YAML::LoadFile("../configs/NamenodeConfig.yaml");
    int SERVER_PORT = node["server_port"].as<int>();

    std::string server_address = "0.0.0.0:" + std::to_string(SERVER_PORT);

    ServerBuilder builder;

    builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());

    builder.RegisterService(m_datanodeService);
    builder.RegisterService(m_clientService);


    auto server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on "<< server_address;

    server->Wait();
}
