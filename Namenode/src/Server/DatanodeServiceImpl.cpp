//
// Created by lxx18 on 2023/8/24.
//

#include "glog/logging.h"
#include "Server/DatanodeServiceImpl.h"

DatanodeServiceImpl::DatanodeServiceImpl(DatanodeManager *manager) :m_manager(manager){

}

DatanodeServiceImpl::~DatanodeServiceImpl() {

}

grpc::Status DatanodeServiceImpl::registerDatanode(::grpc::ServerContext *context,
                                                   const ::DatanodeNamenode::RegisterDatanodeRequest *request,
                                                   ::DatanodeNamenode::RegisterDatanodeResponse *response) {

    auto datanode = new DatanodeInfo();
    datanode->CopyFrom(request->registration().info());

    auto id = new DatanodeID();
    id->CopyFrom(datanode->id());

    m_manager->lock();
    m_manager->addDatanode(datanode);
    m_manager->unlock();
    auto registration = new DatanodeNamenode::DatanodeRegister();
    auto retInfo = new DatanodeInfo();
    retInfo->CopyFrom(*datanode);
    registration->set_allocated_info(retInfo);
    response->set_allocated_registration(registration);

    return grpc::Status::OK;
}

grpc::Status
DatanodeServiceImpl::sendHeartBeat(::grpc::ServerContext *context, const ::DatanodeNamenode::HeartBeatRequest *request,
                                   ::DatanodeNamenode::HeartBeatResponse *response) {

    auto info = new DatanodeInfo();
    info->CopyFrom(request->registration().info());


    auto update = new Report(info, request->xmitsinprogress(), request->failedvolums(),
                             request->cachecapacity(), request->cacheused());


    m_manager->lock();
    auto cmds = m_manager->handleHeartBeat(info->id().datanodeuuid(),update);
    m_manager->unlock();

    delete(update);

    for (auto& cmd:cmds) {
        std::cout << cmd.commandtype() << "\n";
        for (int i = 0; i < cmd.cachecmd().blocks_size(); ++i) {
            std::cout << cmd.cachecmd().blocks(i);
        }
        response->add_cmds()->CopyFrom(cmd);
    }

    for(int i = 0;i < response->cmds_size();i ++){
        auto cmd = response->cmds(i);
        std::cout << cmd.commandtype();
        for (int j = 0; j < cmd.cachecmd().blocks_size(); ++j) {
            auto  b = cmd.cachecmd().blocks(j);
        }
    }
    return grpc::Status::OK;
}

grpc::Status
DatanodeServiceImpl::blockReport(::grpc::ServerContext *context, const ::DatanodeNamenode::blockReportRequest *request,
                                 ::DatanodeNamenode::blockReportResponse *response) {
    return Service::blockReport(context, request, response);
}

grpc::Status
DatanodeServiceImpl::cacheReport(::grpc::ServerContext *context, const ::DatanodeNamenode::cacheReportRequest *request,
                                 ::DatanodeNamenode::cacheReportResponse *response) {
    return Service::cacheReport(context, request, response);
}

grpc::Status DatanodeServiceImpl::blockReceivedAndDeleted(::grpc::ServerContext *context,
                                                          const ::DatanodeNamenode::BlockReceivedAndDeletedRequest *request,
                                                          ::DatanodeNamenode::BlockReceivedAndDeletedResponse *response) {
    return Service::blockReceivedAndDeleted(context, request, response);
}

grpc::Status
DatanodeServiceImpl::errorReport(::grpc::ServerContext *context, const ::DatanodeNamenode::ErrorReportRequest *request,
                                 ::DatanodeNamenode::ErrorReportResponse *response) {
    return Service::errorReport(context, request, response);
}

grpc::Status DatanodeServiceImpl::reportBadBlock(::grpc::ServerContext *context,
                                                 const ::DatanodeNamenode::ReportBadBlockRequest *request,
                                                 ::DatanodeNamenode::ReportBadBlockResponse *response) {
    return Service::reportBadBlock(context, request, response);
}


