//
// Created by lxx18 on 2023/9/11.
//

#ifndef DFSCLIENT_DFSCLIENT_H
#define DFSCLIENT_DFSCLIENT_H


#include <map>
#include <vector>
#include <set>

#include "Client/ClientBase.h"
#include "Client/DatanodeClient.h"
#include "Client/NamenodeClient.h"

class DFSClient : public ClientBase{
private:
    NamenodeClient* m_namenodeClient;
    DatanodeClient* m_datanodeClient;
public:
    DFSClient(NamenodeClient* namenodeClient);
    static DatanodeClient* getDatanode(const std::string& uuid);
    void mkdir(const std::string& path);
    void deleteNode(const std::string& path);
    void rename(const std::string& src,const std::string& dst);
    void listing(const std::string& path);
    void uploadFile(const std::string& dst,const std::string& file);
    void downloadFile(const std::string& dst,const std::string& file);
};


#endif //DFSCLIENT_DFSCLIENT_H
