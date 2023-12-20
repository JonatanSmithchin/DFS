cmake_minimum_required(VERSION 3.22.1)
project(DataNode)

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

target_link_libraries(DataNode PRIVATE dfsProto Client Server utils Cache)

add_custom_command(
        OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/datanode.sh
        COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/datanode.sh
        ${CMAKE_CURRENT_BINARY_DIR}/datanode.sh
        DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/datanode.sh
)

target_sources(DataNode
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/datanode.sh)