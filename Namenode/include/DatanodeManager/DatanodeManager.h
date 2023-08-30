//
// Created by lxx18 on 2023/8/24.
//

#ifndef NAMENODE_DATANODEMANAGER_H
#define NAMENODE_DATANODEMANAGER_H

#include "proto/DatanodeNamenode.pb.h"
#include "proto/dfs.pb.h"
#include "ConsistentHash.h"
#include "Report.h"

using namespace DatanodeNamenode;

class DatanodeManager {
private:
    std::mutex mutex;
    std::map<std::string, DatanodeInfo *> m_datanodeMap;
    ConsistentHash m_consistentHash;
public:
    void lock();

    void unlock();

    explicit DatanodeManager();

    static long long now();

    [[nodiscard]] const std::map<std::string, DatanodeInfo *> &getDatanodeMap() const;

    void addDatanode(DatanodeInfo* d);

    void removeDatanode(DatanodeInfo* d);

    DatanodeInfo* getDatanode(const std::string& uuid);

    DatanodeInfo* chooseDatanode(const std::string& key);

    std::vector<DatanodeCommand> handleHeartBeat(const std::string& uuid, Report* update);
};


#endif //NAMENODE_DATANODEMANAGER_H
