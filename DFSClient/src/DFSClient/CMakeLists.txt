cmake_minimum_required(VERSION 3.22.1)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

aux_source_directory(. DFS_CLIENT)

add_library(dfsClient STATIC ${DFS_CLIENT})

target_link_libraries(dfsClient PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)