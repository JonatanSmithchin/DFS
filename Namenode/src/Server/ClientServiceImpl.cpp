//
// Created by lxx18 on 2023/8/24.
//

#include "Server/ClientServiceImpl.h"

ClientServiceImpl::~ClientServiceImpl() {

}

grpc::Status ClientServiceImpl::GetBlockLocation(::grpc::ServerContext *context,
                                                 const ::ClientNamenode::GetBlockLocationRequest *request,
                                                 ::ClientNamenode::GetBlockLocationResponse *response) {

    return Service::GetBlockLocation(context, request, response);
}

grpc::Status ClientServiceImpl::GetFileBlockLocations(::grpc::ServerContext *context,
                                                      const ::ClientNamenode::GetFileBlockLocationsRequest *request,
                                                      ::ClientNamenode::GetFileBlockLocationsResponse *response) {
    const auto& src= request->src();
    auto blocks = new LocatedBlocks();
    m_nameSystem->readLock();
    blocks->CopyFrom(*m_nameSystem->getBlocks(src));
    m_nameSystem->readUnLock();
    response->set_allocated_locations(blocks);
    return grpc::Status::OK;
}

grpc::Status ClientServiceImpl::GetServerDefaults(::grpc::ServerContext *context,
                                                  const ::ClientNamenode::GetServerDefaultsRequest *request,
                                                  ::ClientNamenode::GetServerDefaultsResponse *response) {
    return Service::GetServerDefaults(context, request, response);
}

grpc::Status ClientServiceImpl::Create(::grpc::ServerContext *context, const ::ClientNamenode::CreateRequest *request,
                                       ::ClientNamenode::CreateResponse *response) {
    std::string src = request->src();
    m_nameSystem->writeLock();
    auto file = m_nameSystem->addFile(src);
    m_nameSystem->writeUnlock();

    if (file != nullptr){
        auto fileStatus = new FileStatus();
        fileStatus->set_path(src);
        fileStatus->set_length(0);
        fileStatus->set_owner(request->clientname());
        fileStatus->set_modification_time(file->getModifiedTime());
        response->set_allocated_status(fileStatus);
        return grpc::Status::OK;
    }

    return grpc::Status::CANCELLED;
}

grpc::Status ClientServiceImpl::Append(::grpc::ServerContext *context, const ::ClientNamenode::AppendRequest *request,
                                       ::ClientNamenode::AppendResponse *response) {
    const auto& src = request->src();
    m_nameSystem->writeLock();
    auto locatedBlock = m_nameSystem->append(src);
    m_nameSystem->writeUnlock();
    if (locatedBlock != nullptr){

        response->set_allocated_block(locatedBlock);
        return grpc::Status::OK;
    }
    return grpc::Status::CANCELLED;
}

grpc::Status ClientServiceImpl::Rename(::grpc::ServerContext *context, const ::ClientNamenode::RenameRequest *request,
                                       ::ClientNamenode::RenameResponse *response) {
    auto src = request->src();
    auto dest = request->dst();
    m_nameSystem->writeLock();

    m_nameSystem->writeUnlock();
    return Service::Rename(context, request, response);
}

grpc::Status ClientServiceImpl::Delete(::grpc::ServerContext *context, const ::ClientNamenode::DeleteRequest *request,
                                       ::ClientNamenode::DeleteResponse *response) {
    m_nameSystem->writeLock();
    auto res = m_nameSystem->remove(request->src());
    m_nameSystem->writeUnlock();
    response->set_result(res);
    return grpc::Status::OK;
}

grpc::Status
ClientServiceImpl::SetPermission(::grpc::ServerContext *context, const ::ClientNamenode::SetPermissionRequest *request,
                                 ::ClientNamenode::SetPermissionResponse *response) {
    return Service::SetPermission(context, request, response);
}

grpc::Status
ClientServiceImpl::SetOwner(::grpc::ServerContext *context, const ::ClientNamenode::SetOwnerRequest *request,
                            ::ClientNamenode::SetOwnerResponse *response) {
    return Service::SetOwner(context, request, response);
}

grpc::Status
ClientServiceImpl::AddBlock(::grpc::ServerContext *context, const ::ClientNamenode::AddBlockRequest *request,
                            ::ClientNamenode::AddBlockResponse *response) {
    return Service::AddBlock(context, request, response);
}

grpc::Status ClientServiceImpl::mkdir(::grpc::ServerContext *context, const ::ClientNamenode::mkdirRequest *request,
                                      ::ClientNamenode::mkdirResponse *response) {
    m_nameSystem->writeLock();
    auto dir = m_nameSystem->addDir(request->src());
    m_nameSystem->writeUnlock();
    if (dir == nullptr){
        return grpc::Status::CANCELLED;
    } else{
        response->set_issuccess(true);
        return grpc::Status::OK;
    }
}

grpc::Status
ClientServiceImpl::Listing(::grpc::ServerContext *context, const ::ClientNamenode::GetListingRequest *request,
                           ::ClientNamenode::GetListingResponse *response) {
    const auto& src = request->src();
    m_nameSystem->readLock();
    auto res = m_nameSystem->list(src);
    m_nameSystem->readUnLock();
    auto list = new DirectoryListing();
    for (auto it:res) {
        auto ele = list->add_partiallisting();
        ele->set_path(it->getName());
        ele->set_length(0);
        ele->set_modification_time(it->getModifiedTime());
    }
    response->set_allocated_dirlist(list);
    return grpc::Status::OK;
}

grpc::Status
ClientServiceImpl::RenewLease(::grpc::ServerContext *context, const ::ClientNamenode::RenewLeaseRequest *request,
                              ::ClientNamenode::RenewLeaseResponse *response) {
    return Service::RenewLease(context, request, response);
}

ClientServiceImpl::ClientServiceImpl(NameSystem *nameSystem):m_nameSystem(nameSystem) {

}



