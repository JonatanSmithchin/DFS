//
// Created by lxx18 on 2023/9/10.
//

#include <grpcpp/grpcpp.h>
#include "glog/logging.h"
#include "proto/ClientDatanode.pb.h"
#include "Client/DatanodeClient.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace ClientDatanode;

int main(int argc,char** argv){
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Starting DFSClient";

    DatanodeClient client(grpc::CreateChannel(
            "localhost:8501",grpc::InsecureChannelCredentials()
            ));

    client.uploadBlock("/mnt/d/cpp-project/DFS/DFSClient/tests/utils/honkai3.jpg");

    return 0;
}