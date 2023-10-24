//
// Created by cyt on 2023/9/27.
//

#ifndef DATANODE_DATANODESERVICEIMPL_H
#define DATANODE_DATANODESERVICEIMPL_H

#include "proto/Datanode.grpc.pb.h"

class DatanodeServiceImpl final : public Datanode::BackupService::Service{
public:
    DatanodeServiceImpl(const std::string& work_dir);

    ~DatanodeServiceImpl() override;

    ::grpc::Status 
    copyBlock(::grpc::ServerContext* context, ::grpc::ServerReader< ::Datanode::copyBlockRequest>* reader,
                ::Datanode::copyBlockResponse* response) override;

private:
    const std::string& m_work_dir;
};


#endif //DATANODE_DATANODESERVICEIMPL_H