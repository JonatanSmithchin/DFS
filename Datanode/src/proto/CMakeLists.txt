cmake_minimum_required(VERSION 3.22.1)
project(dfsProto)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

aux_source_directory(. PROTO_SRC)

add_library(dfsProto SHARED ${PROTO_SRC})

target_link_libraries(dfsProto PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)