//
// Created by 刘骁 on 2023/4/10.
//

#include "INode/INodeDir.h"
#include <algorithm>

bool INodeDir::addChild(INode* child) {
    //TODO: 不能添加相同的child
    children.push_back(child);
    std::sort(children.begin(),children.end());
    return true;
}

bool INodeDir::removeChild(const string &childName) {
    for (auto iter = children.begin();iter != children.end();iter++)
    {
        if (childName == (*iter)->getName()) {
            children.erase(iter);
            std::sort(children.begin(),children.end());
            return true;
         }
    }
    return false;
}

bool INodeDir::replaceChild(INode *child) {
    for (auto iter = children.begin();iter != children.end();iter++)
    {
        if (child->getName() == (*iter)->getName()) {
            iter = children.erase(iter);
            children.push_back(child);
            return true;
        }
    }
    return false;
}

bool INodeDir::clearChildren() {
    return false;
}

INode* INodeDir::getChild(const string &childName) {
    for (auto& c : children)
    {
        if (childName == c->getName()) {
            return c;
        }
    }
    return nullptr;
}

vector<INode *> INodeDir::getChildren() {
    return children;
}

bool INodeDir::isFile() {
    return false;
}

bool INodeDir::isDir() {
    return true;
}

bool INodeDir::isRoot() {
    if (getParent() == nullptr){
        return true;
    }
    return false;
}

bool INodeDir::isSymlink() {
    return false;
}

