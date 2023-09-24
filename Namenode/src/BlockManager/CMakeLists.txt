cmake_minimum_required(VERSION 3.22.1)

find_package(glog CONFIG REQUIRED)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(. BLOCK_MANAGER)

add_library(BlockManager STATIC ${BLOCK_MANAGER})

target_link_libraries(BlockManager PRIVATE glog::glog)

target_link_libraries(BlockManager PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)