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

std::vector<DatanodeInfo*> DatanodeManager::chooseDatanode(const std::string& key) {

    std::vector<DatanodeInfo*> datanodes;
    for (int i = 0; i < 3; ++i) {
        std::string uuid = m_consistentHash.Get(key+std::to_string(i));
        auto datanode = m_datanodeMap.find(uuid)->second;
        datanodes.push_back(datanode);
    }
    return datanodes;
}


std::vector<DatanodeCommand> DatanodeManager::handleHeartBeat(const std::string &uuid, Report* update) {

    LOG(INFO) << "get heartBeat from datanode " << uuid;

    auto datanode = getDatanode(uuid);

    if (datanode == nullptr){
        return {};
    }

    datanode->set_lastupdate(now());
    std::vector<DatanodeCommand> cmds;

    if (backupBlocks.front().first == uuid){
        auto backup = backupBlocks.front();
        backupBlocks.pop();

        auto cmd = new DatanodeCommand;
        cmd->set_commandtype(DatanodeCommand_Type_BlockCommand);

        auto blkCmd = new BlockCommand;
        blkCmd->set_action(BlockCommand_Action_TRANSFER);

        auto blk = blkCmd->add_blocks();
        blk->set_blockid(backup.second);
        auto target = blkCmd->add_targets();
        target->CopyFrom(*m_datanodeMap.find(backup.first)->second);

        cmd->set_allocated_blkcmd(blkCmd);
    }

    return cmds;
}

void DatanodeManager::backupBlock(const pair<std::string, size_t>& backup) {
    backupBlocks.push(backup);
}






