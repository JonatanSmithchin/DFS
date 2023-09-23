//
// Created by lxx18 on 2023/9/12.
//
#include "gtest/gtest.h"
#include "Client/NamenodeClient.h"
#include "grpcpp/grpcpp.h"

TEST(TEST_CREATE,test_create1){
    NamenodeClient client(grpc::CreateChannel(
            "localhost:8500",grpc::InsecureChannelCredentials()
    ));

    auto res = client.create("/hello");
    ASSERT_EQ(res,true);
}

TEST(TEST_APPEND,test_append1){
    NamenodeClient client(grpc::CreateChannel(
            "localhost:8500",grpc::InsecureChannelCredentials()
    ));

    auto res = client.create("/hello");
    ASSERT_EQ(res,true);

    auto block = client.append("/hello");
    for (const auto& it:block->locs()) {
        std::cout << it.id().ipaddr() << ":" << it.id().xferport();
    }
    std::cout << block->block().generationstamp();
    delete block;
}

// TEST(TEST_LOCATE,test_locate1){
//     NamenodeClient client(grpc::CreateChannel(
//             "localhost:8500",grpc::InsecureChannelCredentials()
//     ));
// }