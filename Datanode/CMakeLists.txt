cmake_minimum_required(VERSION 3.22.1)
project(DataNode)

list(APPEND CMAKE_MODULE_PATH "/home/parallels/Desktop/vcpkg/scripts/buildsystems")
include(vcpkg)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

find_package(glog CONFIG REQUIRED)

find_package(YAML-CPP REQUIRED)

set(DATA_NODE_HOME ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_DIRS)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(tests)

add_subdirectory(src)

add_executable(DataNode ${SRC_DIRS})

target_link_libraries(DataNode PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

target_link_libraries(DataNode PRIVATE glog::glog yaml-cpp)

target_link_libraries(DataNode PRIVATE dfsProto Client Server utils)