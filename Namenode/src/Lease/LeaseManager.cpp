//
// Created by lxx18 on 2023/8/28.
//

#include <list>
#include <vector>
#include <algorithm>
#include "Lease/LeaseManager.h"

bool LeaseManager::check() {
    bool needSyn = false;

    for(;!m_sortedLeases.empty();){
        const auto oldest = m_sortedLeases.begin();

        if(!(*oldest).expiredSoftLimit()){
            return needSyn;
        }

        std::list<std::string> removing;
        std::vector<std::string> paths((*oldest).getPaths().size());
        std::copy((*oldest).getPaths().begin(), (*oldest).getPaths().end(),paths.begin());
        for(const std::string& s: paths){

        }
    }
    return needSyn;
}

Lease *LeaseManager::add(const std::string& holder) {

    auto lease = new Lease(holder);
    m_leases.insert(std::map<std::string,Lease>::value_type(holder,*lease));
    m_sortedLeases.insert(*lease);
    return lease;
}

void LeaseManager::renewLease(const std::string& holder) {

    auto kv = m_leases.find(holder);
    auto it = m_sortedLeases.find(kv->second);

    if (it != m_sortedLeases.end()){
        m_sortedLeases.erase(it);
    }

    kv->second.setLastUpdated();
    m_sortedLeases.insert(kv->second);
}

void LeaseManager::remove(const std::string &holder) {

    auto kv = m_leases.find(holder);

    auto lease = kv->second;

    m_sortedLeases.erase(lease);

    delete(&lease);
}
