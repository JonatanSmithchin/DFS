//
// Created by lxx18 on 2023/8/24.
//

#ifndef NAMENODE_DATANODEMANAGER_H
#define NAMENODE_DATANODEMANAGER_H

#include "proto/DatanodeNamenode.pb.h"
#include "proto/dfs.pb.h"
#include "ConsistentHash.h"
#include "Report.h"
#include "BlockManager/BlockManager.h"
#include "DatanodeDescriptor.h"

using namespace DatanodeNamenode;

class DatanodeManager {
private:
    std::mutex mutex;
    std::map<std::string, DatanodeDescriptor *> m_datanodeMap;
    ConsistentHash m_consistentHash;
    queue<pair<std::string ,size_t>> backupBlocks;
    BlockManager* m_blockManager;
public:
    void lock();

    void unlock();

    explicit DatanodeManager();

    explicit DatanodeManager(BlockManager* blockManager);

    static long long now();

    [[nodiscard]] const std::map<std::string, DatanodeDescriptor *> &getDatanodeMap() const;

    void addDatanode(DatanodeInfo* d);

    void removeDatanode(DatanodeInfo* d);

    void backupBlock(const pair<std::string,size_t>& backup);

    DatanodeInfo* getDatanode(const std::string& uuid);

    DatanodeDescriptor* getDatanodeDes(const std::string& uuid);

    std::vector<DatanodeInfo*> chooseDatanode(const std::string& key);

    std::vector<DatanodeCommand> handleHeartBeat(const std::string& uuid, Report* update);
};


#endif //NAMENODE_DATANODEMANAGER_H
