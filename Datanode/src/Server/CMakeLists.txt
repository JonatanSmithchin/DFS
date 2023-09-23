cmake_minimum_required(VERSION 3.22.1)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(. SERVER)

add_library(Server STATIC ${SERVER})

target_link_libraries(Server PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

target_link_libraries(Server PRIVATE glog::glog)