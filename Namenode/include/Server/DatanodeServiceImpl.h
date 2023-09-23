//
// Created by lxx18 on 2023/8/24.
//

#ifndef NAMENODE_DATANODESERVICEIMPL_H
#define NAMENODE_DATANODESERVICEIMPL_H

#include "proto/DatanodeNamenode.grpc.pb.h"
#include "DatanodeManager/DatanodeManager.h"

class DatanodeServiceImpl final :public DatanodeNamenode::DatanodeService::Service{
private:
    DatanodeManager* m_manager;
public:
    explicit DatanodeServiceImpl(DatanodeManager* manager);

    ~DatanodeServiceImpl() override;

    grpc::Status
    registerDatanode(::grpc::ServerContext *context, const ::DatanodeNamenode::RegisterDatanodeRequest *request,
                     ::DatanodeNamenode::RegisterDatanodeResponse *response) override;

    grpc::Status sendHeartBeat(::grpc::ServerContext *context, const ::DatanodeNamenode::HeartBeatRequest *request,
                               ::DatanodeNamenode::HeartBeatResponse *response) override;

    grpc::Status blockReport(::grpc::ServerContext *context, const ::DatanodeNamenode::blockReportRequest *request,
                             ::DatanodeNamenode::blockReportResponse *response) override;

    grpc::Status cacheReport(::grpc::ServerContext *context, const ::DatanodeNamenode::cacheReportRequest *request,
                             ::DatanodeNamenode::cacheReportResponse *response) override;

    grpc::Status blockReceivedAndDeleted(::grpc::ServerContext *context,
                                         const ::DatanodeNamenode::BlockReceivedAndDeletedRequest *request,
                                         ::DatanodeNamenode::BlockReceivedAndDeletedResponse *response) override;

    grpc::Status errorReport(::grpc::ServerContext *context, const ::DatanodeNamenode::ErrorReportRequest *request,
                             ::DatanodeNamenode::ErrorReportResponse *response) override;

    grpc::Status
    reportBadBlock(::grpc::ServerContext *context, const ::DatanodeNamenode::ReportBadBlockRequest *request,
                   ::DatanodeNamenode::ReportBadBlockResponse *response) override;
};


#endif //NAMENODE_DATANODESERVICEIMPL_H
