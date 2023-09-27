#include "BlockManager/BlockManager.h"
#include <string>
#include <utility>
BlockManager::BlockManager() {
    hashTableSize = 379;
    hashKey = 53;
    hashTableSize2 = 9973;
    hashKey2 = 113;
    num = 0;
    hashTable1 = new vector<BlockIndexHash*>;
    hashTable1->reserve(hashTableSize);
    for(int i = 0;i < hashTable1->capacity();i++){
        hashTable1->push_back(new BlockIndexHash);
    }

}

bool BlockManager::create(const string& name){
    return (*hashTable1)[getKey(name, hashTableSize, hashKey)]->insert(name, getKey(name, hashTableSize2, hashKey2), new LocatedBlocks);
}

LocatedBlock* BlockManager::addBlock(size_t blockID, const vector<DatanodeInfo*>& datanodes, int size,const string& name) {
    auto blockMessage = getALLBlock(name);
    auto m = blockMessage->add_blocks();
    Block *B;
    B = new Block;
    B->set_blockid(blockID);
    B->set_generationstamp(time(nullptr));
    B->set_size(size);
    m->set_allocated_block(B);
    for (auto & datanode : datanodes) {
        DatanodeInfo *D = m->add_locs();
        D->CopyFrom(*datanode);
    }
    m->set_offset(blockMessage->blocks_size());
    auto block = new LocatedBlock();
    block->CopyFrom(*m);
    return block;
}

int BlockManager::getKey(string name, int hashsize, int key) {
    int x = 0;
    for (int i = 0; i < name.size(); i++) {
        x = (x * key + name[i]) % hashsize;
    }
    return x;
}

bool BlockManager::removeBlock(string name) {
    return (*hashTable1)[getKey(name, hashTableSize, hashKey)]->remove(getKey(name, hashTableSize2, hashKey2), name);
}
LocatedBlocks* BlockManager::getALLBlock(string name) {

    auto res = (*hashTable1)[getKey(name, hashTableSize, hashKey)]->inquireALL(getKey(name, hashTableSize2, hashKey2), name);
    for (int i = 0; i < res->blocks_size(); ++i) {
        auto datanode = res->blocks(i).locs(0);
        auto locs = datanode.id().ipaddr();
        auto port  = datanode.id().xferport();
        std::cout << locs << ":" << port;
    }
    return res;
}

const LocatedBlock* BlockManager::getBlock(string name, uint64_t blockID) {
    return (*hashTable1)[getKey(name, hashTableSize, hashKey)]->inquire(getKey(name, hashTableSize2, hashKey2), name, blockID);
}

