//
// Created by lxx18 on 2023/8/25.
//

#include <yaml-cpp/yaml.h>
#include "NameSystem/NameSystem.h"
#include "sstream"

YAML::Node node = YAML::LoadFile("../configs/NamenodeConfig.yaml");
int blockId = node["first_block_id"].as<int>();

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
    file->setName(getFileName(path));
    auto now =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch());
    file->setModifiedTime(now.count());
    std::hash<INodeFile*> hash;
    file->setId(hash(file));
    return file;
}

NameSystem::NameSystem(INodeDir *root, DatanodeManager *manager, BlockManager *blockManager)
    :m_root(root),m_datanodeManager(manager),m_blockManager(blockManager) {
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

bool NameSystem::removeFile(const string &path) {
    auto p = findParent(path);
    if (p == nullptr){
        return false;
    }
    return p->removeChild(getFileName(path));
}

LocatedBlock* NameSystem::append(const string &path) {
    auto file = find(path);
    if (file == nullptr){
        return nullptr;
    } else{
        //TODO: blockManager构建block元数据

//        auto block = new Block();
//
//        block->set_blockid(blockId++);
//        block->set_generationstamp(
//                std::chrono::duration_cast<std::chrono::milliseconds>(
//                        std::chrono::system_clock::now().time_since_epoch()).count()
//        );
//
//        //选择datanode构造locatedBlock
//        auto locatedBlock = new LocatedBlock();
//        locatedBlock->set_allocated_block(block);
//        auto datanode = locatedBlock->add_locs();
        auto datanode = m_datanodeManager->chooseDatanode(std::to_string(file->getId()));

        auto lblock = m_blockManager->addBlock(blockId++,std::vector<DatanodeInfo*>{datanode},BLOCK_SIZE,path);
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
    //    auto file = find(path);
//    if (file != nullptr && file->isFile()){
//        auto map = dynamic_cast<INodeFile*>(file)->getBlocks();
//        auto blocks = new LocatedBlocks();
//        for (auto it : map){
//            auto block = blocks->add_blocks();
//            block->set_allocated_block();
//        }
//        return blocks;
//    }
    return m_blockManager->getALLBlock(path);
}





