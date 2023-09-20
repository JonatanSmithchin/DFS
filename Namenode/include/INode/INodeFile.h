//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_INODEFILE_H
#define DFSFORCPP_INODEFILE_H
#include "INode.h"
#include <map>

class INodeFile :public INode{
private:
    long header;
public:
    bool isFile() override;

    bool isDir() override;

    bool isRoot() override;

    bool isSymlink() override;

//    void addBlock(LocatedBlock* block);
//
//    LocatedBlock* getBlock(int offset);
//
//    [[nodiscard]] const std::map<int, LocatedBlock *> &getBlocks() const;
};


#endif //DFSFORCPP_INODEFILE_H
