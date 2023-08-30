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
