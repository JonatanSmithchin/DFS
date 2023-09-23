//
// Created by lxx18 on 2023/8/28.
//

#ifndef NAMENODE_REPORT_H
#define NAMENODE_REPORT_H

#include "proto/dfs.pb.h"

class Report {
private:
    DatanodeInfo* m_info;
public:
    DatanodeInfo *getMInfo() const;

    uint getMXmitsInProgress() const;

    uint getMFailedVolums() const;

    uint getMCacheCapacity() const;

    uint getMCacheUsed() const;

private:
    uint m_xmitsInProgress;
    uint m_failedVolums;
    uint m_cacheCapacity;
    uint m_cacheUsed;
public:
    Report(DatanodeInfo *info, uint mitsInProgress, uint failedVolums, uint cacheCapacity,
           uint cacheUsed);

    ~Report();

    void update(Report *update);
};


#endif //NAMENODE_REPORT_H
