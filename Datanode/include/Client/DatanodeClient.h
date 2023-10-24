//
// Created by cyt on 2023/10/13.
//

#ifndef DATANODE_DATANODECLIENT_H
#define DATANODE_DATANODECLIENT_H

#include "proto/Datanode.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace Datanode;

#define CHUNK_SIZE 1024 * 1024

class DatanodeClient{
private:
    const std::string m_work_dir;
    std::unique_ptr<BackupService::Stub> m_stub;

public:
    // explicit DatanodeClient(std::shared_ptr<grpc::Channel> channel, const std::string& work_dir);

    explicit DatanodeClient(std::shared_ptr<Channel> channel, const std::string& work_dir): m_stub(BackupService::NewStub(channel)), m_work_dir(work_dir) {
    
    }
    
    void copyBlock(uint64_t blockId);
};
#endif // DATANODE_DATANODECLIENT_H
