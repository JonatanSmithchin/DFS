cmake_minimum_required(VERSION 3.22.1)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

find_package(YAML-CPP REQUIRED)

aux_source_directory(. CLIENT)

add_library(Client STATIC ${CLIENT})

target_link_libraries(Client PRIVATE dfsProto)

target_link_libraries(Client PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

target_link_libraries(Client PRIVATE glog::glog)

target_link_libraries(Client PRIVATE yaml-cpp)