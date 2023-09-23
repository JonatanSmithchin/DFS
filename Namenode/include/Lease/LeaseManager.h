//
// Created by lxx18 on 2023/8/28.
//

#ifndef NAMENODE_LEASEMANAGER_H
#define NAMENODE_LEASEMANAGER_H


#include <map>
#include <string>
#include "Lease.h"

class LeaseManager {
private:
    std::map<std::string,Lease> m_leases;
    std::set<Lease> m_sortedLeases;
public:
    Lease* add(const std::string& holder);
    void renewLease(const std::string& holder);
    bool check();
    void remove(const std::string& holder);
};



#endif //NAMENODE_LEASEMANAGER_H
