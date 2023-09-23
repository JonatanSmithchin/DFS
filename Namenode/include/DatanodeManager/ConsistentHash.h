//
// Created by lxx18 on 2023/8/24.
//

#ifndef NAMENODE_CONSISTENTHASH_H
#define NAMENODE_CONSISTENTHASH_H


#include <functional>
#include "proto/dfs.pb.h"

class ConsistentHash {
private:
    std::hash<std::string> m_hash;
    int m_replicas;
    std::vector<std::size_t> keys;
    std::map<std::size_t,std::string> hashMap;
public:
    ConsistentHash();
    explicit ConsistentHash(int replicas);
    void Add(const std::string& key);
    std::string Get(const std::string& key);
    void Delete(const std::string& key);
};

#endif //NAMENODE_CONSISTENTHASH_H
