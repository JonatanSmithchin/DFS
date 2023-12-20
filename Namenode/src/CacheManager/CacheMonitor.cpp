//
// Created by lxx18 on 2023/12/19.
//

#include <thread>
#include "CacheManager/CacheMonitor.h"
#include "glog/logging.h"

[[noreturn]] void CacheMonitor::rescan() {
    while(true){

        std::this_thread::sleep_for(std::chrono::seconds(5));

        LOG(INFO) << "check caches";
//        if (m_manager->cachingBlocks.empty()){
//            LOG(INFO) << "empty caches";
//            continue;
//        }
        auto shouldCached = m_manager->m_policy.getHashmap();
        for (auto it:shouldCached) {
            if (std::find(cachedBlocks.begin(), cachedBlocks.end(),it.second->value) != cachedBlocks.end()){
                continue;
            }
            cachingBlocks.push_back(it.second->value);
        }
        LOG(INFO) << "pend cache";
        addNewPendingCached();
    }
}

void CacheMonitor::addNewPendingCached() {
    m_dnManager->lock();
    for (auto& lb:cachingBlocks) {
        auto uuid = lb->locs(0).id().datanodeuuid();
        auto des = m_dnManager->getDatanodeDes(uuid);
        if (des == nullptr){
            m_dnManager->unlock();
            return;
        }
        //在datanode中增加缓存项
        LOG(INFO) << uuid << " cached " << lb->block().blockid();
        cachedBlocks.push_back(lb);
        des->pendCache(lb->block().blockid());
    }
    m_dnManager->unlock();
    cachingBlocks.clear();
}

CacheMonitor::CacheMonitor(CacheManager *manager, DatanodeManager *dnManager):m_manager(manager),m_dnManager(dnManager) {

}

void CacheMonitor::run() {
    std::thread monitor(&CacheMonitor::rescan,this);
    if (monitor.joinable()){
        LOG(INFO) << "Cache monitor started.";
        monitor.detach();
    } else{
        LOG(ERROR) << "Cannot start cache monitor!";
    }
}
