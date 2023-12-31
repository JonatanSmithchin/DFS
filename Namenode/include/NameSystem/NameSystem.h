//
// Created by lxx18 on 2023/8/25.
//

#ifndef NAMENODE_NAMESYSTEM_H
#define NAMENODE_NAMESYSTEM_H


#include <mutex>
#include "INode/INodeDir.h"
#include "DatanodeManager/DatanodeManager.h"
#include "INode/INodeFile.h"
#include "BlockManager/BlockManager.h"
#include "CacheManager/CacheManager.h"

constexpr size_t BLOCK_SIZE = 64 * 1024 * 1024;
class NameSystem {
private:
    int readCount;
    std::mutex readMtx;
    std::mutex writeMtx;
    INodeDir *m_root;
    INodeDir* workingDir;
    DatanodeManager* m_datanodeManager;
    BlockManager* m_blockManager;
    CacheManager* m_cacheManager;
    INode* find(const std::string& path);
    INodeDir* findParent(const std::string& path);
    static INodeFile* constructFile(const std::string& path);
    void backupBlocks();
    void cache(const string& path,uint64_t blk);
public:
    NameSystem(INodeDir* root,DatanodeManager* manager,BlockManager* blockManager,CacheManager* cacheManager);
    void readLock();
    void writeLock();
    void readUnLock();
    void writeUnlock();
    INodeDir* getRoot();
    INode* addFile(const std::string& path);
    bool remove(const std::string& path);
    LocatedBlock* append(const std::string& path);
    LocatedBlocks* getBlocks(const std::string& path);
    INode* addDir(const std::string& path);
    vector<INode*> list(const std::string& path);
};

std::string getPrePath(const std::string& path);
#endif //NAMENODE_NAMESYSTEM_H
