//
// Created by lxx18 on 2023/8/26.
//

#ifndef NAMENODE_NAMENODECLIENT_H
#define NAMENODE_NAMENODECLIENT_H

#include "proto/DatanodeNamenode.grpc.pb.h"
#include "Cache/Cache.h"
#include <grpcpp/grpcpp.h>
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace DatanodeNamenode;

class NameNodeClient{
private:
    DatanodeID* m_id;
    std::unique_ptr<DatanodeService::Stub> m_stub;
    Cache* m_cache;
    void cache(std::vector<uint64_t> blks);
    [[noreturn]] void heartBeat();
public:
    NameNodeClient(std::shared_ptr<grpc::Channel> channel,Cache* cache);

    void registration();

    std::vector<DatanodeCommand> sendHeartBeat();

    void run();
};
#endif //NAMENODE_NAMENODECLIENT_H
