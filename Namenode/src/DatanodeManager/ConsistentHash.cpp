//
// Created by lxx18 on 2023/8/24.
//

#include <yaml-cpp/yaml.h>
#include "../../include/DatanodeManager/ConsistentHash.h"

ConsistentHash::ConsistentHash() {
    YAML::Node node = YAML::LoadFile("../configs/NamenodeConfig.yaml");
    m_replicas = node["replicas"].as<int>();
}

ConsistentHash::ConsistentHash(int replicas) {
    m_replicas = replicas;
}

void ConsistentHash::Add(const std::string &key) {
    for (int i = 0; i < m_replicas; i ++){
        std::size_t hash = m_hash(std::to_string(i).append(key));
        keys.push_back(hash);
        hashMap.insert(std::map<std::size_t,std::string>::value_type (hash,key));
    }
    std::sort(keys.begin(), keys.end());
}

std::string ConsistentHash::Get(const std::string &key) {
    if (keys.empty()){
        return {};
    }

    std::size_t hash = m_hash(key);

    auto index = std::find_if(keys.begin(), keys.end(),
                             [hash] (std::size_t ele){return ele >= hash;});

    auto uuid = hashMap.find(keys[(*index)%keys.size()])->second;
    return uuid;
}

void ConsistentHash::Delete(const std::string &key) {
    for (int i = 0; i < m_replicas; i ++){

        std::size_t hash = m_hash(std::to_string(i).append(key));

        auto iter = std::remove(keys.begin(), keys.end(),hash);
        keys.erase(iter,keys.end());

        hashMap.erase(hash);
    }
    std::sort(keys.begin(), keys.end());
}


