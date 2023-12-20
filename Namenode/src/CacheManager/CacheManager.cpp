//
// Created by lxx18 on 2023/12/19.
//

#include "CacheManager/CacheManager.h"

void CacheManager::addCache(const LocatedBlock* lb) {
    m_policy.put(lb->block().blockid(),lb);
}

CacheManager::CacheManager(int capacity): m_policy(LRU(capacity)) {

}

bool CacheManager::cached(uint64_t blkId) {
    return m_policy.Cached(blkId);
}
