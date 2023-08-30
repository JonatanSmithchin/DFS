//
// Created by lxx18 on 2023/8/25.
//

#include "NameSystem/NameSystem.h"
#include "sstream"

vector<std::string> resolvePath(const string& path){
    std::stringstream ss(path);
    char c = '/';
    vector<string> res;
    if (path[0] == '/'){
        res.emplace_back("/");
    }
    string s;
    while (getline(ss,s,c)){
        if (s.empty()){
            continue;
        }
        res.push_back(s);
    }
    return res;
}

std::string getFileName(const string& path){
    return path.substr(path.find_last_of('/'),-1);
}

std::string getPrePath(const std::string& path){
    return path.substr(0,path.find_last_of('/'));
}

INode *NameSystem::find(const string &path) {
    vector<string> paths = resolvePath(path);

    INode* node;

    if (paths[0] == "/"){
        node = static_cast<INode *>(m_root);
    } else{
        node = static_cast<INode *>(workingDir);
    }

    for(int i = 0; i < paths.size() - 1; i ++){
        if (node->isDir()){
            auto dir = dynamic_cast<INodeDir*>(node);
            INode *child = dir->getChild(paths[i+1]);
            if (child == nullptr){
                return nullptr;
            }
            node = child;
        } else{
            return nullptr;
        }
    }
    return node;
}

INodeDir *NameSystem::findParent(const string &path) {
    return dynamic_cast<INodeDir *>(find(getPrePath(path)));
}

INodeFile *NameSystem::constructFile(const string &path) {
    auto file = new INodeFile();
    file->setFullPathName(path);
    auto now =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch());
    file->setModifiedTime(now.count());
    std::hash<INodeFile*> hash;
    file->setId(hash(file));
    return file;
}

NameSystem::NameSystem(INodeDir *root, DatanodeManager *manager):m_root(root),m_datanodeManager(manager) {
    readCount = 0;
    workingDir = m_root;
}

void NameSystem::readLock() {
    readMtx.lock();
    if (++readCount == 1){
        writeMtx.lock();
    }

    readMtx.unlock();
}

void NameSystem::writeLock() {
    writeMtx.lock();
}

void NameSystem::readUnLock() {
    readMtx.lock();
    if (--readCount == 0){
        writeMtx.unlock();
    }
    readMtx.unlock();
}

void NameSystem::writeUnlock() {
    writeMtx.unlock();
}

INodeDir *NameSystem::getRoot() {
    return m_root;
}

INode *NameSystem::addFile(const string &path) {
    auto p = findParent(path);
    if (p == nullptr){
        return p;
    }
    auto f = constructFile(path);
    p->addChild(f);

    return f;
}

bool NameSystem::removeFile(const string &path) {
    return false;
}

LocatedBlock* NameSystem::append(const string &path) {
    auto file = find(path);
    if (file == nullptr){
        return nullptr;
    } else{

        auto datanode = m_datanodeManager->chooseDatanode(std::to_string(file->getId()));

        auto locatedBlock = new LocatedBlock();
        datanode = locatedBlock->add_locs();

        return locatedBlock;
    }
}

INode *NameSystem::addDir(const string &path) {
    return nullptr;
}

vector<INode *> NameSystem::list(const string &path) {
    INode* dir = find(path);
    if (!dir->isDir()){
        return {};
    }
    return dynamic_cast<INodeDir*>(dir)->getChildren();
}




