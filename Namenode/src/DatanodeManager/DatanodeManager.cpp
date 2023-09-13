//
// Created by lxx18 on 2023/8/24.
//

#include "glog/logging.h"
#include "DatanodeManager/DatanodeManager.h"
#include <utility>


DatanodeManager::DatanodeManager(){
    m_consistentHash = ConsistentHash();
}

void DatanodeManager::lock() {
    mutex.lock();
}

void DatanodeManager::unlock() {
    mutex.unlock();
}

long long DatanodeManager::now() {
    return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

const std::map<std::string, DatanodeInfo *> &DatanodeManager::getDatanodeMap() const {
    return m_datanodeMap;
}

void DatanodeManager::addDatanode(DatanodeInfo *d) {
    std::string uuid = d->id().datanodeuuid();
    d->set_lastupdate(now());
    m_datanodeMap.insert(std::map<std::string,DatanodeInfo*>::value_type(uuid,d));
    m_consistentHash.Add(uuid);
    LOG(INFO) << "add datanode " << d->id().hostname();
}


void DatanodeManager::removeDatanode(DatanodeInfo *d) {
    std::string uuid = d->id().datanodeuuid();

    auto it = m_datanodeMap.find(uuid);
    if (it == m_datanodeMap.end()){
        return;
    }
    auto dead = it->second;
    m_datanodeMap.erase(it);

    delete(dead);
    m_consistentHash.Delete(uuid);


}

DatanodeInfo *DatanodeManager::getDatanode(const std::string &uuid) {
    auto it = m_datanodeMap.find(uuid);
    if (it == m_datanodeMap.end()){
        return nullptr;
    }
    auto datanode = it->second;
    return datanode;
}

DatanodeInfo *DatanodeManager::chooseDatanode(const std::string& key) {

    std::string uuid = m_consistentHash.Get(key);
    auto datanode = m_datanodeMap.find(uuid)->second;
    return datanode;
}


std::vector<DatanodeCommand> DatanodeManager::handleHeartBeat(const std::string &uuid, Report* update) {

    LOG(INFO) << "get heartBeat from datanode " << uuid;

    auto datanode = getDatanode(uuid);

    if (datanode == nullptr){
        return {};
    }

    datanode->set_lastupdate(now());
    std::vector<DatanodeCommand> cmds;


    return cmds;
}






