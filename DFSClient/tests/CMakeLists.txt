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

add_executable(test_NamenodeClient Client/test_NamenodeClient.cpp)

add_test(NAME test_NamenodeClient COMMAND test_create)

target_link_libraries(test_NamenodeClient PRIVATE Client gtest gtest_main )

target_link_libraries(test_NamenodeClient PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

add_executable(test_DFSClient DFSClient/test_DFSClient.cpp)

add_test(NAME test_DFSClient COMMAND test_DFSClient)

target_link_libraries(test_DFSClient PRIVATE dfsClient Client dfsProto utils gtest gtest_main)

target_link_libraries(test_DFSClient PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)