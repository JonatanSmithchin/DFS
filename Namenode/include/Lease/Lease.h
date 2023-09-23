//
// Created by lxx18 on 2023/8/28.
//

#ifndef NAMENODE_LEASE_H
#define NAMENODE_LEASE_H


#include <ctime>
#include <string>
#include <set>

#define SOFT_EXPIRED_INTERVAL std::chrono::seconds(60).count()
#define HARD_EXPIRED_INTERVAL std::chrono::seconds(1800).count()

class Lease {
private:
    std::string m_holder;
    time_t lastUpdated;
    std::set<std::string> m_paths;
    [[nodiscard]] static long long now() ;

public:
    Lease(std::string  holder);

    bool operator < (const Lease& lease) const;

    [[nodiscard]] const std::string &getMHolder() const;

    [[nodiscard]] time_t getLastUpdated() const;

    void setLastUpdated();

    [[nodiscard]] const std::set<std::string> &getMPaths() const;

public:
    void renew(const std::string& holder,std::set<std::string> paths);
    [[nodiscard]] std::set<std::string> getPaths() const;
    [[nodiscard]] bool expiredSoftLimit() const;
    [[nodiscard]] bool expiredHardLimit() const;
};


#endif //NAMENODE_LEASE_H
