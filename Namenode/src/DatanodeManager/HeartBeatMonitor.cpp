//
// Created by lxx18 on 2023/8/25.
//

#include <thread>
#include "glog/logging.h"
#include "DatanodeManager/HeartBeatMonitor.h"
#include <yaml-cpp/yaml.h>

auto node = YAML::LoadFile("../configs/NamenodeConfig.yaml");
auto CHECK_INTERVAL = std::chrono::seconds(node["check_interval"].as<int>()).count();

HeartBeatMonitor::HeartBeatMonitor(DatanodeManager *manager):m_manager(manager){}

void HeartBeatMonitor::checkHeartBeat() {
    bool isAllAlive = false;
    while (!isAllAlive){

        DatanodeInfo* dead;

        std::this_thread::sleep_for(std::chrono::seconds(10));

        auto now = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch())
                        .count();

        m_manager->lock();
        LOG(INFO) << "check DataNodes";

        if (m_manager->getDatanodeMap().empty()){
            m_manager->unlock();
            continue;
        }

        for (const auto& it:m_manager->getDatanodeMap()) {
            auto info = it.second->getInfo();
            LOG(INFO) << "check status: " << info->id().hostname();
            if (info->lastupdate() + CHECK_INTERVAL < now){
                dead = info;
            }
        }
        if (dead != nullptr){
            LOG(INFO) << "remove datanode " << dead->id().hostname();
            m_manager->removeDatanode(dead);
        }
        m_manager->unlock();
    }
}

void HeartBeatMonitor::run() {
    std::thread monitor(&HeartBeatMonitor::checkHeartBeat,this);
    if (monitor.joinable()){
        LOG(INFO) << "Monitor started.";
        monitor.detach();
    } else{
        LOG(ERROR) << "Cannot start monitor!";
    }
}


