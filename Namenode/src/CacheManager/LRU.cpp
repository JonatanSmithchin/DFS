//
// Created by lxx18 on 2023/12/20.
//

#include "CacheManager/LRU.h"


LRU::LRU(int capacity):m_capacity(capacity) {

}

void LRU::remove(Node *node) {
    if (node->pre != nullptr){
        node->pre->next = node->next;
    } else{
        head = node->next;
    }
    if (node->next != nullptr){
        node->next->pre = node->pre;
    }else{
        tail = node->pre;
    }
}

void LRU::setHead(Node *node) {
    node->next = head;
    node->pre = nullptr;

    if (head != nullptr){
        head->pre = node;
    }
    head = node;
    if (tail == nullptr){
        tail = head;
    }
}

const LocatedBlock* LRU::get(uint64_t blkId) {
    auto it = hashmap.find(blkId);
    if (it == hashmap.end()){
        return nullptr;
    } else{
        auto node = it->second;
        remove(node);
        setHead(node);
        return node->value;
    }
}

void LRU::put(uint64_t blkId, const LocatedBlock *lb) {
    auto it = hashmap.find(blkId);
    if (it != hashmap.end()){
        auto node = it->second;
        node->value = lb;
        remove(node);
        setHead(node);
    } else{
        auto node = new Node(blkId,lb);
        if (hashmap.size() >= m_capacity){
            it = hashmap.find(tail->blkId);
            remove(tail);
            delete it->second;
            hashmap.erase(it);
        }
        setHead(node);
        hashmap[blkId] = node;
    }
}

bool LRU::Cached(uint64_t blkId) {
    return !(hashmap.find(blkId) == hashmap.end());
}

const std::map<uint64_t, Node *> &LRU::getHashmap() const {
    return hashmap;
}
