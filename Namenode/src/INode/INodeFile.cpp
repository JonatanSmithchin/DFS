//
// Created by 刘骁 on 2023/4/10.
//

#include "INode/INodeFile.h"


bool INodeFile::isFile() {
    return true;
}

bool INodeFile::isDir() {
    return false;
}

bool INodeFile::isRoot() {
    return false;
}

bool INodeFile::isSymlink() {
    return false;
}

//void INodeFile::addBlock(LocatedBlock *block) {
//    blocksMap.insert(std::pair<int,LocatedBlock*>(block->offset(),block));
//}
//
//LocatedBlock* INodeFile::getBlock(int offset) {
//    auto it = blocksMap.find(offset);
//    if (it == blocksMap.end()){
//        return nullptr;
//    }
//    return it->second;
//}
//
//const std::map<int, LocatedBlock *> &INodeFile::getBlocks() const {
//    return blocksMap;
//}
