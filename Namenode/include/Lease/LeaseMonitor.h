//
// Created by lxx18 on 2023/8/28.
//

#ifndef NAMENODE_LEASEMONITOR_H
#define NAMENODE_LEASEMONITOR_H

#include "LeaseManager.h"

class LeaseMonitor {
private:
    LeaseManager* m_manager;
public:
    explicit LeaseMonitor(LeaseManager* manager);
    void checkLease();
    void run();
};


#endif //NAMENODE_LEASEMONITOR_H
