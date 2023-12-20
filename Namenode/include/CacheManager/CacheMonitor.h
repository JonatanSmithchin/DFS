//
// Created by lxx18 on 2023/12/19.
//

#ifndef NAMENODE_CACHEMONITOR_H
#define NAMENODE_CACHEMONITOR_H


#include <vector>
#include "proto/dfs.pb.h"
#include "CacheManager.h"
#include "DatanodeManager/DatanodeManager.h"

class CacheMonitor {
private:
    CacheManager* m_manager;
    DatanodeManager* m_dnManager;
    std::vector<const LocatedBlock*> cachedBlocks;
    std::vector<const LocatedBlock*> cachingBlocks;

    [[noreturn]] void rescan();
    void addNewPendingCached();
public:
    CacheMonitor(CacheManager * manager, DatanodeManager* dnManager);

    void run();
};


#endif //NAMENODE_CACHEMONITOR_H
