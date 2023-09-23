cmake_minimum_required(VERSION 3.22.1)

find_package(glog CONFIG REQUIRED)

find_package(YAML-CPP REQUIRED)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(. DATA_NODE_MANAGER)

add_library(DatanodeManager STATIC ${DATA_NODE_MANAGER})

target_link_libraries(DatanodeManager PRIVATE glog::glog)

target_link_libraries(DatanodeManager PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
        yaml-cpp)