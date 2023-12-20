//
// Created by lxx18 on 2023/12/19.
//

#include "DatanodeManager/DatanodeDescriptor.h"

DatanodeInfo *DatanodeDescriptor::getInfo() const {
    return info;
}

void DatanodeDescriptor::setInfo(DatanodeInfo *info) {
    DatanodeDescriptor::info = info;
}

void DatanodeDescriptor::pendCache(uint64_t blk) {
    pendingCached.push(blk);
}

uint64_t DatanodeDescriptor::cache() {
    auto blk_id = pendingCached.front();
    pendingCached.pop();
    return blk_id;
}

bool DatanodeDescriptor::pendingCacheEmpty() {
    return pendingCached.empty();
}
