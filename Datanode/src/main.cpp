//
// Created by lxx18 on 2023/8/26.
//

#include <grpcpp/grpcpp.h>
#include <glog/logging.h>
#include <yaml-cpp/yaml.h>

#include "proto/DatanodeNamenode.grpc.pb.h"
#include "Client/NamenodeClient.h"
#include "Server/ClientDatanodeServiceImpl.h"
#include "Server/RPCServer.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace DatanodeNamenode;

int main(int argc,char** argv) {
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Starting DataNode";

    YAML::Node node = YAML::LoadFile("../configs/DatanodeConfig.yaml");

    std::string NAMENODE_HOST = node["client_host"].as<std::string>();
    int NAMENODE_PORT = node["client_port"].as<int>();

    std::string client_addr = NAMENODE_HOST + ":" +std::to_string(NAMENODE_PORT);

    NameNodeClient client(grpc::CreateChannel(
            client_addr, grpc::InsecureChannelCredentials()
    ));

    client.registration();

    client.run();

    const std::string& work_dir = node["work_dir"].as<std::string>();

    ClientDatanodeServiceImpl ClientDatanodeService(work_dir);
    DatanodeServiceImpl DatanodeService(work_dir);

    RPCServer server(&ClientDatanodeService,&DatanodeService);

    server.RunServer();

    return 0;
}