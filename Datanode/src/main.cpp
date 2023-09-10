//
// Created by lxx18 on 2023/8/26.
//

#include <grpcpp/grpcpp.h>
#include <glog/logging.h>
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

    NameNodeClient client(grpc::CreateChannel(
            "localhost:8500", grpc::InsecureChannelCredentials()
    ));

    client.registration();

    client.run();

    const std::string& work_dir = "/mnt/d/test/";

    ClientDatanodeServiceImpl ClientDatanodeService(work_dir);

    RPCServer server(&ClientDatanodeService);

    server.RunServer();

    return 0;
}