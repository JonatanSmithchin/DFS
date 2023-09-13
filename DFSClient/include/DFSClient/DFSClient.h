//
// Created by lxx18 on 2023/9/11.
//

#ifndef DFSCLIENT_DFSCLIENT_H
#define DFSCLIENT_DFSCLIENT_H


#include <map>
#include "Client/DatanodeClient.h"
#include "Client/NamenodeClient.h"

class DFSClient {
private:
    NamenodeClient* m_namenodeClient;
public:
    DFSClient(NamenodeClient* namenodeClient);
    static DatanodeClient* getDatanode(const std::string& uuid);
    void uploadFile(const std::string& dst,const std::string& file);
};


#endif //DFSCLIENT_DFSCLIENT_H
