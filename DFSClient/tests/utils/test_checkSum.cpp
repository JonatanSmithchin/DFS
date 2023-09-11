//
// Created by lxx18 on 2023/9/10.
//
#include <fstream>
#include "utils/FileUtils.h"
#include "gtest/gtest.h"

TEST(TEST_CHECKSUM,test_checkSum1){
    const char *hello = "hello";
    std::cout << checkSum((const unsigned char*)hello, strlen(hello));
}

TEST(TEST_CHECKSUM,test_checkSum2){
    char data[64];

    std::ifstream infile;
    infile.open("/mnt/d/cpp-project/DFS/DFSClient/tests/utils/test.txt",std::ifstream::in | std::ifstream::binary);

    while (true){
        infile.read(data,64);
        long size = infile.gcount();
        std::cout << checkSum((const unsigned char*)data,size) << std::endl;
        if (infile.eof()){
            break;
        }
    }
    infile.close();
}