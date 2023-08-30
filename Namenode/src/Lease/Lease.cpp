//
// Created by lxx18 on 2023/8/28.
//

#include <chrono>
#include <utility>
#include "Lease/Lease.h"

std::set<std::string> Lease::getPaths() const {
    return m_paths;
}

void Lease::renew(const std::string& holder,std::set<std::string> paths) {
    m_holder = holder;
    lastUpdated = now();
    m_paths = std::move(paths);
}

bool Lease::expiredSoftLimit() const{
    return now() > (lastUpdated + SOFT_EXPIRED_INTERVAL);
}

bool Lease::expiredHardLimit() const{
    return now() > (lastUpdated + HARD_EXPIRED_INTERVAL);
}

long long Lease::now() {
    return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

const std::string &Lease::getMHolder() const {
    return m_holder;
}

time_t Lease::getLastUpdated() const {
    return lastUpdated;
}

const std::set<std::string> &Lease::getMPaths() const {
    return m_paths;
}

Lease::Lease(std::string holder) :m_holder(holder){
    lastUpdated = now();
}

bool Lease::operator<(const Lease &lease) const {
    return lastUpdated < lease.getLastUpdated();
}

void Lease::setLastUpdated() {
    lastUpdated = now();
}


