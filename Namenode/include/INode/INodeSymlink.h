//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_INODESYMLINK_H
#define DFSFORCPP_INODESYMLINK_H

#include <string>
#include "INode.h"

using std::string;
class INodeSymlink:INode {
    bool isFile() override;

    bool isDir() override;

    bool isRoot() override;

    bool isSymlink() override;

private:
    string link;
};


#endif //DFSFORCPP_INODESYMLINK_H
