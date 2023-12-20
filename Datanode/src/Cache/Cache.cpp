//
// Created by lxx18 on 2023/12/19.
//

#include <fstream>
#include <utility>
#include "Cache/Cache.h"

bool Cache::hit(uint64_t blk) {
    readLock();
    auto res = !(mappableBlockMap.find(blk) == mappableBlockMap.end());
    readUnLock();
    return res;
}

char* Cache::get(uint64_t blk) {
    readLock();
    auto& res = mappableBlockMap.find(blk)->second;
    readUnLock();
    return res.content;
}

void Cache::cacheBlock(uint64_t blkId) {
    writeLock();
    std::string file = m_workdir + std::to_string(blkId);
    std::ifstream infile(file,std::ifstream::in|std::ifstream::binary);
    if (infile.is_open()){
        writeUnlock();
        return;
    }
    auto cache_blk = new Value;
    while (!infile.eof()){
        infile.read(cache_blk->content,1024*1024*64);
    }
    mappableBlockMap.insert(std::map<uint64_t,Value&>::value_type (blkId,*cache_blk));
    writeUnlock();
}

void Cache::unCacheBlock(uint64_t blkId) {

}

Cache::Cache(std::string workdir) : m_workdir(std::move(workdir)) {}

void Cache::readLock() {
    readMtx.lock();
    if (++readCount == 1){
        writeMtx.lock();
    }

    readMtx.unlock();
}

void Cache::writeLock() {
    writeMtx.lock();
}

void Cache::readUnLock() {
    readMtx.lock();
    if (--readCount == 0){
        writeMtx.unlock();
    }
    readMtx.unlock();
}

void Cache::writeUnlock() {
    writeMtx.unlock();
}
