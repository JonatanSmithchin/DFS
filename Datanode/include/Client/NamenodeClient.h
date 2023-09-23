//
// Created by lxx18 on 2023/8/26.
//

#ifndef NAMENODE_NAMENODECLIENT_H
#define NAMENODE_NAMENODECLIENT_H

#include "proto/DatanodeNamenode.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace DatanodeNamenode;

class NameNodeClient{
private:
    std::unique_ptr<DatanodeService::Stub> m_stub;

    [[noreturn]] void heartBeat();
public:
    explicit NameNodeClient(std::shared_ptr<grpc::Channel> channel);

    void registration();

    std::vector<DatanodeCommand> sendHeartBeat();

    void run();
};
#endif //NAMENODE_NAMENODECLIENT_H
