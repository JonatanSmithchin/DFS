//
// Created by lxx18 on 2023/9/11.
//

#include <fstream>
#include "gtest/gtest.h"
#include "utils/FileUtils.h"

TEST(TEST_SPLITFile,test_splitFile1){
    std::fstream input("/mnt/d/test/test128M.jpg",std::ios::in);
    FileUtils::SplitFile(&input,"/mnt/d/test/temp/upload");
}

TEST(TEST_MERGEFILE,test_mergeFile1){
    std::fstream output("/mnt/d/test/testRes.jpg",std::ios::out|std::ios::binary);
    std::vector<std::string> files;
    files.push_back("/mnt/d/test/rcv/114514");
    files.push_back("/mnt/d/test/rcv/114515");

    FileUtils::MergeFile(&output,files);
}

TEST(TEST_GETFILES,test_getFiles){
    auto res = FileUtils::getFiles("/mnt/d/test/temp/upload");
    for (auto it:res){
        std::cout << it;
    }
}