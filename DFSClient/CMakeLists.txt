cmake_minimum_required(VERSION 3.22.1)
project(DFSClient)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

find_package(glog CONFIG REQUIRED)

find_package(Boost CONFIG REQUIRED COMPONENTS program_options)

set(CLIENT_HOME ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_DIRS)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(tests)

add_subdirectory(src)

add_executable(DFSClient ${SRC_DIRS})

target_link_libraries(DFSClient PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

target_link_libraries(DFSClient PRIVATE glog::glog)

target_link_libraries(DFSClient PRIVATE dfsClient Client dfsProto utils)