//
// Created by lxx18 on 2023/8/24.
//

#ifndef NAMENODE_CLIENTSERVICEIMPL_H
#define NAMENODE_CLIENTSERVICEIMPL_H

#include "proto/ClientNamenode.grpc.pb.h"
#include "NameSystem/NameSystem.h"

class ClientServiceImpl final : public ClientNamenode::ClientService::Service{
private:
    NameSystem* m_nameSystem;
public:
    ClientServiceImpl(NameSystem* nameSystem);

    ~ClientServiceImpl() override;

    grpc::Status
    GetBlockLocation(::grpc::ServerContext *context, const ::ClientNamenode::GetBlockLocationsRequest *request,
                     ::ClientNamenode::GetBlockLocationResponse *response) override;

    grpc::Status
    GetServerDefaults(::grpc::ServerContext *context, const ::ClientNamenode::GetServerDefaultsRequest *request,
                      ::ClientNamenode::GetServerDefaultsResponse *response) override;

    grpc::Status Create(::grpc::ServerContext *context, const ::ClientNamenode::CreateRequest *request,
                        ::ClientNamenode::CreateResponse *response) override;

    grpc::Status Append(::grpc::ServerContext *context, const ::ClientNamenode::AppendRequest *request,
                        ::ClientNamenode::AppendResponse *response) override;

    grpc::Status Rename(::grpc::ServerContext *context, const ::ClientNamenode::RenameRequest *request,
                        ::ClientNamenode::RenameResponse *response) override;

    grpc::Status Delete(::grpc::ServerContext *context, const ::ClientNamenode::DeleteRequest *request,
                        ::ClientNamenode::DeleteResponse *response) override;

    grpc::Status SetPermission(::grpc::ServerContext *context, const ::ClientNamenode::SetPermissionRequest *request,
                               ::ClientNamenode::SetPermissionResponse *response) override;

    grpc::Status SetOwner(::grpc::ServerContext *context, const ::ClientNamenode::SetOwnerRequest *request,
                          ::ClientNamenode::SetOwnerResponse *response) override;

    grpc::Status AddBlock(::grpc::ServerContext *context, const ::ClientNamenode::AddBlockRequest *request,
                          ::ClientNamenode::AddBlockResponse *response) override;

    grpc::Status mkdir(::grpc::ServerContext *context, const ::ClientNamenode::mkdirRequest *request,
                       ::ClientNamenode::mkdirResponse *response) override;

    grpc::Status Listing(::grpc::ServerContext *context, const ::ClientNamenode::GetListingRequest *request,
                         ::ClientNamenode::GetListingResponse *response) override;

    grpc::Status RenewLease(::grpc::ServerContext *context, const ::ClientNamenode::RenewLeaseRequest *request,
                            ::ClientNamenode::RenewLeaseResponse *response) override;

};


#endif //NAMENODE_CLIENTSERVICEIMPL_H
