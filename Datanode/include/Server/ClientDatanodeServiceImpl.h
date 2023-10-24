//
// Created by lxx18 on 2023/9/9.
//

#ifndef DATANODE_CLIENTDATANODESERVICEIMPL_H
#define DATANODE_CLIENTDATANODESERVICEIMPL_H
#define CHUNK_SIZE 1024 * 1024
#include "proto/ClientDatanode.grpc.pb.h"
#include "Client/DatanodeClient.h"

class ClientDatanodeServiceImpl final : public ClientDatanode::FileService::Service{
public:
    ClientDatanodeServiceImpl(const std::string& work_dir);

    ~ClientDatanodeServiceImpl() override;

    grpc::Status
    transferBlock(::grpc::ServerContext *context, ::grpc::ServerReader<::ClientDatanode::transferBlockRequest> *reader,
                  ::ClientDatanode::transferBlockResponse *response) override;

    grpc::Status downloadBlock(::grpc::ServerContext *context, const ::ClientDatanode::downloadBlockRequest *request,
                               ::grpc::ServerWriter<::ClientDatanode::downloadBlockResponse> *writer) override;

private:
    const std::string& m_work_dir;
};


#endif //DATANODE_CLIENTDATANODESERVICEIMPL_H
