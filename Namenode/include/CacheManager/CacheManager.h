//
// Created by lxx18 on 2023/12/19.
//

#ifndef NAMENODE_CACHEMANAGER_H
#define NAMENODE_CACHEMANAGER_H


#include <map>
#include <string>
#include "proto/dfs.pb.h"
#include "LRU.h"

//TODO: 淘汰缓存的算法LRU
class CacheManager {
private:
    LRU m_policy;
    friend class CacheMonitor;
public:
    explicit CacheManager(int capacity);
    void addCache(const LocatedBlock* lb);
    bool cached(uint64_t blkId);
};


#endif //NAMENODE_CACHEMANAGER_H
