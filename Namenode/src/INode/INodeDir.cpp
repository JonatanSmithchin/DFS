//
// Created by 刘骁 on 2023/4/10.
//

#include "INode/INodeDir.h"

bool INodeDir::addChild(INode* child) {
    children.push_back(child);
    return true;
}

bool INodeDir::removeChild(const string &childName) {
    for (vector<INode*>::iterator iter = children.begin();iter != children.end();iter++)
    {
        if (childName.compare((*iter)->getName()) == 0) {
            iter = children.erase(iter);
            return true;
         }
    }
    return false;
}

bool INodeDir::replaceChild(INode *child) {
    for (vector<INode*>::iterator iter = children.begin();iter != children.end();iter++)
    {
        if (child->getName().compare((*iter)->getName()) == 0) {
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
        if (childName.compare(c->getName()) == 0) {
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

