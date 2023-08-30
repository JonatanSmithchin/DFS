//
// Created by lxx18 on 2023/8/26.
//

#include "utils/net_utils.h"
#include "gtest/gtest.h"

TEST(TEST_GET_NETINFO,test_get_netinfo1){
    std::string  hostname;
    std::string ip;
    GetHostInfo(hostname,ip);
    std::cout << hostname << " : " << ip;
}
