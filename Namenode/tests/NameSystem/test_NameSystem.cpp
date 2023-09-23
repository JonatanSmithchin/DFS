//
// Created by lxx18 on 2023/8/25.
//
#include "gtest/gtest.h"
#include "NameSystem/NameSystem.h"

TEST(tes_get_prePath,test_get_prePath1){
    std::cout << getPrePath("/hello/good/hello.txt");
    ASSERT_EQ("/hello/good", getPrePath("/hello/good/hello.txt"));
}

// TEST(test_add_file,test_add_file1){

// }