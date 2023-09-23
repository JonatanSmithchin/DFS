cmake_minimum_required(VERSION 3.22.1)
project(tests)

add_subdirectory(../third_party/googletest googletest)
include_directories(${NAME_NODE_HOME}/third_party/googletest/googletest/include)

set(GTEST_LIB gtest gtest_main)

add_executable(test_add_node DataNodeManager/ConsistentHash/test_add.cpp)
add_executable(test_get_prePath NameSystem/test_NameSystem.cpp)

target_link_libraries(test_add_node gtest gtest_main)

add_test(NAME test_add_node COMMAND test_add_node)

target_link_libraries(test_get_prePath gtest gtest_main DatanodeManager NameSystem dfsProto)

target_link_libraries(test_get_prePath gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

add_test(NAME test_get_prePath COMMAND test_get_prePath)