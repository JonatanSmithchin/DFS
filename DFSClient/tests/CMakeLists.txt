cmake_minimum_required(VERSION 3.22.1)
project(tests)

add_subdirectory(../third_party/googletest googletest)
include_directories(${DATA_NODE_HOME}/third_party/googletest/googletest/include)
set(GTEST_LIB gtest gtest_main)

add_executable(test_checkSum utils/test_checkSum.cpp)

add_test(NAME test_checkSum COMMAND test_checkSum)

target_link_libraries(test_checkSum gtest gtest_main utils)

add_executable(test_splitFile utils/test_splitFile.cpp)

add_test(NAME test_splitFile COMMAND test_splitFile test_mergeFile)

target_link_libraries(test_splitFile gtest gtest_main utils)