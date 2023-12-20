//
// Created by lxx18 on 2023/12/19.
//

#ifndef DATANODE_CACHE_H
#define DATANODE_CACHE_H


#include <map>
#include <cstdint>
#include <mutex>
class Value{
public:
    char content[64*1024*1024];
};

class Cache {
private:
    int readCount;
    std::mutex readMtx;
    std::mutex writeMtx;
    std::string m_workdir;
    std::map<uint64_t,Value&>  mappableBlockMap;
public:
    void readLock();
    void writeLock();
    void readUnLock();
    void writeUnlock();
    explicit Cache(std::string workdir);
    bool hit(uint64_t blk);
    char* get(uint64_t blk);
    void cacheBlock(uint64_t blkId);
    void unCacheBlock(uint64_t blkId);
};


#endif //DATANODE_CACHE_H
