//
// Created by lxx18 on 2023/8/28.
//

#include <thread>
#include "glog/logging.h"
#include "Lease/LeaseMonitor.h"

LeaseMonitor::LeaseMonitor(LeaseManager *manager):m_manager(manager) {}

void LeaseMonitor::checkLease() {
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        LOG(INFO) << "check leases";

        bool needSync = m_manager->check();

        if (needSync){

        }
    }
}

void LeaseMonitor::run() {
    std::thread monitor(&LeaseMonitor::checkLease,this);
    if (monitor.joinable()){
        LOG(INFO) << "Lease monitor started.";
        monitor.detach();
    } else{
        LOG(ERROR) << "Cannot start lease monitor!";
    }
}


