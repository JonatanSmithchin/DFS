cmake_minimum_required(VERSION 3.22.1)
project(NameNode)

find_package(gRPC CONFIG REQUIRED)

find_package(Protobuf REQUIRED)

find_package(glog CONFIG REQUIRED)

find_package(YAML-CPP CONFIG REQUIRED)

set(NAME_NODE_HOME ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_DIRS)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(tests)

add_subdirectory(src)

add_executable(NameNode ${SRC_DIRS})

target_link_libraries(NameNode PRIVATE gRPC::grpc++ gRPC::grpc++_reflection
        gRPC::gpr gRPC::grpc gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

target_link_libraries(NameNode PRIVATE glog::glog yaml-cpp)

target_link_libraries(NameNode PRIVATE dfsProto Server NameSystem DatanodeManager BlockManager INode)

add_custom_command(
        OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/namenode.sh
        COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/namenode.sh
        ${CMAKE_CURRENT_BINARY_DIR}/namenode.sh
        DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/namenode.sh
)

target_sources(NameNode
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/namenode.sh)