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

const std::map<std::string, DatanodeDescriptor *> &DatanodeManager::getDatanodeMap() const {
    return m_datanodeMap;
}

void DatanodeManager::addDatanode(DatanodeInfo *d) {
    std::string uuid = d->id().datanodeuuid();
    d->set_lastupdate(now());

    auto dd = new DatanodeDescriptor;
    dd->setInfo(d);
    m_datanodeMap.insert(std::map<std::string,DatanodeDescriptor*>::value_type(uuid,dd));
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
    return getDatanodeDes(uuid)->getInfo();
}

std::vector<DatanodeInfo*> DatanodeManager::chooseDatanode(const std::string& key) {

    std::vector<DatanodeInfo*> datanodes;
//    datanodes.reserve(m_datanodeMap.size());
//    for(auto& it:m_datanodeMap){
//        datanodes.push_back(it.second);
//    }
    for (int i = 0; i < 3; ++i) {
        std::string uuid = m_consistentHash.Get(key+std::to_string(i));
        auto datanode = m_datanodeMap.find(uuid)->second;
        datanodes.push_back(datanode->getInfo());
    }
    return datanodes;
}


std::vector<DatanodeCommand> DatanodeManager::handleHeartBeat(const std::string &uuid, Report* update) {

    LOG(INFO) << "get heartBeat from datanode " << uuid;

    auto des = getDatanodeDes(uuid);
    auto info = des->getInfo();


    if (info == nullptr){
        return {};
    }
    LOG(INFO) << info->id().ipaddr() << ":" << info->id().xferport();

    info->set_lastupdate(now());
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
        target->CopyFrom(*m_datanodeMap.find(backup.first)->second->getInfo());

        cmd->set_allocated_blkcmd(blkCmd);
    }
    if (!des->pendingCacheEmpty()){
        DatanodeCommand cmd;
        cmd.set_commandtype(DatanodeCommand_Type_CacheCommand);
        CacheCommand cacheCmd;

        while(!des->pendingCacheEmpty()){
            cacheCmd.add_blocks(des->cache());
        }
        cmd.mutable_cachecmd()->CopyFrom(cacheCmd);
        cmds.push_back(cmd);
    }

    return cmds;
}

void DatanodeManager::backupBlock(const pair<std::string, size_t>& backup) {
    backupBlocks.push(backup);
}

DatanodeManager::DatanodeManager(BlockManager* blockManager):m_blockManager(blockManager) {

}

DatanodeDescriptor *DatanodeManager::getDatanodeDes(const string &uuid) {
    auto it = m_datanodeMap.find(uuid);
    if (it == m_datanodeMap.end()){
        return nullptr;
    }
    auto datanode = it->second;
    return datanode;
}






