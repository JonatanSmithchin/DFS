cmake_minimum_required(VERSION 3.22.1)

find_package(YAML-CPP CONFIG REQUIRED)

add_library(NameSystem SHARED NameSystem.cpp)

target_link_libraries(NameSystem PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
        yaml-cpp)

target_link_libraries(NameSystem PRIVATE INode dfsProto)