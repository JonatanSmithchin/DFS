//
// Created by lxx18 on 2023/12/19.
//

#ifndef NAMENODE_DATANODEDESCRIPTOR_H
#define NAMENODE_DATANODEDESCRIPTOR_H


#include <queue>
#include "proto/dfs.pb.h"

class DatanodeDescriptor {
private:
    DatanodeInfo* info;
    std::queue<uint64_t> pendingCached;
public:
    DatanodeInfo *getInfo() const;

    void setInfo(DatanodeInfo *info);

    bool pendingCacheEmpty();
    void pendCache(uint64_t blk);
    uint64_t cache();
};


#endif //NAMENODE_DATANODEDESCRIPTOR_H
