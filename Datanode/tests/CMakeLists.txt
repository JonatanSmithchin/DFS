cmake_minimum_required(VERSION 3.22.1)
project(tests)

add_subdirectory(../third_party/googletest googletest)
include_directories(${DATA_NODE_HOME}/third_party/googletest/googletest/include)
set(GTEST_LIB gtest gtest_main)

add_executable(test_get_netInfo net_utils/test_net_utils.cpp)

target_link_libraries(test_get_netInfo gtest gtest_main)

add_test(NAME test_get_netInfo COMMAND test_get_netInfo)

target_link_libraries(test_get_netInfo gtest gtest_main utils)

