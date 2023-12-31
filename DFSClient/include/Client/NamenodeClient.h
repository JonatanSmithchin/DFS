//
// Created by lxx18 on 2023/9/11.
//

#ifndef DFSCLIENT_NAMENODECLIENT_H
#define DFSCLIENT_NAMENODECLIENT_H

#include "proto/ClientNamenode.grpc.pb.h"
#include "Client/ClientBase.h"
#include <grpcpp/grpcpp.h>
#include "memory"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace ClientNamenode;

class NamenodeClient : public ClientBase{
private:
    std::unique_ptr<ClientService::Stub> m_stub;
public:
    explicit NamenodeClient(std::shared_ptr<grpc::Channel> channel);
    bool create(const std::string& path);
    LocatedBlock* append(const std::string& path);
    bool rename(const std::string& src,const std::string& dst);
    bool deleteFile(const std::string& path);
    bool mkdir(const std::string& path);
    std::vector<FileStatus> listing(const std::string& path);
    void setPermission(const std::string& path);
    void setOwner(const std::string& path,const std::string& owner);
    void addBlock(const std::string& blkId);
    LocatedBlocks *locate(const std::string& path);
};


#endif //DFSCLIENT_NAMENODECLIENT_H
