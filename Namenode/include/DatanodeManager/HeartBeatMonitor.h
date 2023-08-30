//
// Created by lxx18 on 2023/8/25.
//

#ifndef NAMENODE_HEARTBEATMONITOR_H
#define NAMENODE_HEARTBEATMONITOR_H

#include "DatanodeManager.h"

class HeartBeatMonitor {
private:
    DatanodeManager* m_manager;
    void checkHeartBeat();
public:
    explicit HeartBeatMonitor(DatanodeManager* manager);
    void run();
};


#endif //NAMENODE_HEARTBEATMONITOR_H
