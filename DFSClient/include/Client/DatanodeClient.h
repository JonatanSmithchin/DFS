//
// Created by lxx18 on 2023/9/10.
//

#ifndef DFSCLIENT_DATANODECLIENT_H
#define DFSCLIENT_DATANODECLIENT_H

#define CHUNK_SIZE 1024 * 1024

#include "proto/ClientDatanode.grpc.pb.h"
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace ClientDatanode;

class DatanodeClient {
private:
    std::unique_ptr<FileService::Stub> m_stub;
public:
    explicit DatanodeClient(std::shared_ptr<grpc::Channel> channel);

    void uploadBlock(const std::string& file,uint64_t blockId);
};


#endif //DFSCLIENT_DATANODECLIENT_H
