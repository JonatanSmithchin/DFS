//
// Created by lxx18 on 2023/8/28.
//

#include "DatanodeManager/Report.h"

Report::Report(DatanodeInfo *info, uint xmitsInProgress, uint failedVolums,
               uint cacheCapacity, uint cacheUsed):m_info(info),
                                       m_xmitsInProgress(xmitsInProgress),
                                       m_failedVolums(failedVolums),
                                       m_cacheCapacity(cacheCapacity),
                                       m_cacheUsed(cacheUsed) {
}

DatanodeInfo *Report::getMInfo() const {
    return m_info;
}

uint Report::getMXmitsInProgress() const {
    return m_xmitsInProgress;
}

uint Report::getMFailedVolums() const {
    return m_failedVolums;
}

uint Report::getMCacheCapacity() const {
    return m_cacheCapacity;
}

uint Report::getMCacheUsed() const {
    return m_cacheUsed;
}

void Report::update(Report *update) {

    auto info = update->m_info;

    m_info->CopyFrom(*info);


    m_cacheCapacity = update->getMCacheCapacity();
    m_xmitsInProgress = update->getMXmitsInProgress();
    m_cacheUsed = update->getMCacheUsed();
    m_failedVolums = update->getMFailedVolums();
}

Report::~Report() {
    delete(m_info);
}
