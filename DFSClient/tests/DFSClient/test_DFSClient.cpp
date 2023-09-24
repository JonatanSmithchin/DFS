//
// Created by lxx18 on 2023/9/12.
//
#include "gtest/gtest.h"
#include "DFSClient/DFSClient.h"
#include "grpcpp/grpcpp.h"

TEST(TEST_UPLOADFILE,test_uploadFile1){
    auto namenodeClient = new NamenodeClient(grpc::CreateChannel(
            "localhost:8500",grpc::InsecureChannelCredentials())
                    );
    auto client = new DFSClient(namenodeClient);
    client->uploadFile("/good","/mnt/d/test/test128M.jpg");
}

TEST(TEST_DOWNLOAD,test_downloadFile){
    auto namenodeClient = new NamenodeClient(grpc::CreateChannel(
            "localhost:8500",grpc::InsecureChannelCredentials())
    );
    auto client = new DFSClient(namenodeClient);
    client->uploadFile("/good","/mnt/d/test/test128M.jpg");
    client->downloadFile("/mnt/d/test/download.jpg","/good");
}

