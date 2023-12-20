//
// Created by lxx18 on 2023/12/20.
//

#ifndef NAMENODE_LRU_H
#define NAMENODE_LRU_H


#include <cstdint>
#include <list>
#include "proto/dfs.pb.h"
struct Node{
    uint64_t blkId;
    const LocatedBlock* value;
    Node *pre,*next;
    Node(uint64_t k,const LocatedBlock* v):blkId(k),value(v),pre(nullptr),next(nullptr){}
};

class LRU {
private:
    int m_capacity;
    Node *head,*tail ;
    std::map<uint64_t ,Node*> hashmap;
    void remove(Node *node);
    void setHead(Node *node);
public:
    const std::map<uint64_t, Node *> &getHashmap() const;

    explicit LRU(int capacity);
    bool Cached(uint64_t blkId);
    const LocatedBlock* get(uint64_t blkId);
    void put(uint64_t blkId,const LocatedBlock* lb);

};


#endif //NAMENODE_LRU_H
