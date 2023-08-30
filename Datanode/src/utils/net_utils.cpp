//
// Created by lxx18 on 2023/8/26.
//

#include "utils/net_utils.h"
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

bool GetHostInfo(std::string& hostname,std::string& Ip){
    char name[256];
    gethostname(name,sizeof(name));
    hostname = name;

    struct hostent* host = gethostbyname(name);
    char ipStr[32];
    if(inet_ntop(host->h_addrtype,host->h_addr_list[0],ipStr,sizeof(ipStr)) == nullptr){
        return false;
    }
    Ip = ipStr;
    return true;
}