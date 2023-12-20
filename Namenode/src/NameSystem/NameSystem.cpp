//
// Created by lxx18 on 2023/8/25.
//

#include <yaml-cpp/yaml.h>
#include <thread>
#include "NameSystem/NameSystem.h"
#include "sstream"

YAML::Node node = YAML::LoadFile("../configs/NamenodeConfig.yaml");
size_t blockId = node["first_block_id"].as<size_t>();

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

std::string getName(const string& path){
    return path.substr(path.find_last_of('/')+1,-1);
}

std::string getPrePath(const std::string& path){
    if (path.find_last_of('/') == 0){
        return "/";
    }
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
    file->setName(getName(path));
    auto now =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch());
    file->setModifiedTime(now.count());
    std::hash<INodeFile*> hash;
    file->setId(hash(file));
    return file;
}

NameSystem::NameSystem(INodeDir *root, DatanodeManager *manager, BlockManager *blockManager, CacheManager* cacheManager)
    :m_root(root),m_datanodeManager(manager),m_blockManager(blockManager),m_cacheManager(cacheManager) {
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
    if (m_blockManager->create(path)){
        auto f = constructFile(path);
        p->addChild(f);
        return f;
    }
    return nullptr;
}

bool NameSystem::remove(const string &path) {
    auto p = findParent(path);
    if (p == nullptr){
        return false;
    }
    return p->removeChild(getName(path));
}

LocatedBlock* NameSystem::append(const string &path) {
    auto file = find(path);
    if (file == nullptr){
        return nullptr;
    } else{
        //TODO: blockManager构建block元数据
        auto datanodes = m_datanodeManager->chooseDatanode(std::to_string(blockId++));

        auto lblock = m_blockManager->addBlock(blockId,datanodes,BLOCK_SIZE,path);
//      dynamic_cast<INodeFile*>(file)->addBlock(lblock);

        auto locatedBlock = new LocatedBlock();
        locatedBlock->CopyFrom(*lblock);

        return locatedBlock;
    }
}

INode *NameSystem::addDir(const string &path) {
    auto p = findParent(path);
    auto dir = new INodeDir();
    //TODO: INodeDir构造函数
    dir->setFullPathName(path);
    dir->setName(getName(path));
    p->addChild(dir);
    return dir;
}

vector<INode *> NameSystem::list(const string &path) {
    INode* dir = find(path);
    if (!dir->isDir()){
        return {};
    }
    return dynamic_cast<INodeDir*>(dir)->getChildren();
}

LocatedBlocks* NameSystem::getBlocks(const string &path) {
    auto lblks = m_blockManager->getALLBlock(path);
    for(int i = 0;i < lblks->blocks().size();i++){
        cache(path,lblks->blocks(i).block().blockid());
    }
    return lblks;
}

void NameSystem::backupBlocks() {
    while (true){

        std::this_thread::sleep_for(std::chrono::seconds(60));

        auto blkQueue = m_blockManager->checkBackups();

        while (!blkQueue.empty()){
            auto backup = blkQueue.front();
            blkQueue.pop();
        }
    }
}

void NameSystem::cache(const std::string& path,uint64_t blk) {
    m_cacheManager->addCache(m_blockManager->getBlock(path,blk));
}





