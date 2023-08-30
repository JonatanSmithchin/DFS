//
// Created by 刘骁 on 2023/4/10.
//

#include "INode/INodeSymlink.h"

bool INodeSymlink::isFile() {
    return false;
}

bool INodeSymlink::isDir() {
    return false;
}

bool INodeSymlink::isRoot() {
    return false;
}

bool INodeSymlink::isSymlink() {
    return true;
}
