//
// Created by lxx18 on 2023/8/26.
//

#include <thread>
#include <glog/logging.h>
#include "Client/NamenodeClient.h"
#include "utils/net_utils.h"
#include "proto/dfs.grpc.pb.h"


NameNodeClient::NameNodeClient(std::shared_ptr<Channel> channel): m_stub(DatanodeService::NewStub(channel)) {
}

void NameNodeClient::heartBeat(){
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(60));

        LOG(INFO) << "sending heartbeat";
        auto cmds = sendHeartBeat();

        for(auto it : cmds){
            LOG(INFO) << "do command" << it.commandtype();
        }
    }
}

void NameNodeClient::registration() {

    std::cout << "registering datanode" << std::endl;

    auto id = new DatanodeID();
    std::string hostname,ip;
    GetHostInfo(hostname,ip);
    id->set_ipaddr(ip);
    id->set_hostname(hostname);

    //TODO: 根据配置读取其他信息
    std::hash<DatanodeID*> hash;

    auto uuid = new std::string {std::to_string(hash(id))};
    id->set_allocated_datanodeuuid(uuid);

    auto info = new DatanodeInfo();

    info->set_allocated_id(id);

    auto registration = new DatanodeRegister();

    registration->set_allocated_info(info);

    RegisterDatanodeRequest request;

    request.set_allocated_registration(registration);

    RegisterDatanodeResponse response;
    ClientContext context;

    auto status = m_stub->registerDatanode(&context,request,&response);


    if (status.ok()){
        std::cout << "register datanode " << hostname << " to NameNode" << std::endl;
    }else{
        std::cout << status.error_code() << " : " << status.error_message() << std::endl;
    }
}

std::vector<DatanodeCommand> NameNodeClient::sendHeartBeat() {

    auto id = new DatanodeID();
    std::string hostname,ip;
    GetHostInfo(hostname,ip);
    id->set_ipaddr(ip);
    id->set_hostname(hostname);

    //TODO: 根据配置读取其他信息
    std::hash<DatanodeID*> hash;

    auto uuid = new std::string {std::to_string(hash(id))};
    id->set_allocated_datanodeuuid(uuid);

    auto info = new DatanodeInfo();

    info->set_allocated_id(id);

    auto registration = new DatanodeRegister();

    registration->set_allocated_info(info);

    HeartBeatRequest request;

    request.set_allocated_registration(registration);
    request.set_cachecapacity(0);
    request.set_cacheused(0);
    request.set_failedvolums(0);
    request.set_xceivercount(0);

    HeartBeatResponse response;
    ClientContext context;

    auto status = m_stub->sendHeartBeat(&context,request,&response);

    std::vector<DatanodeCommand> cmds(response.cmds_size());

    for (int i = 0; i < response.cmds_size(); i ++){
        cmds.push_back(response.cmds(i));
    }

    return cmds;
}

void NameNodeClient::run() {
    std::thread heartBeat(&NameNodeClient::heartBeat,this);
    if (heartBeat.joinable()){
        LOG(INFO) << "heartBeat started";
        heartBeat.join();
    } else{
        LOG(ERROR) << "Cannot start heartBeat";
    }
}


