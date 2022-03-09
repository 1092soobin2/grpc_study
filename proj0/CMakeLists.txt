cmake_minimum_required(VERSION 3.5.1)

project(proj0 C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(_PROTOBUF protobuf REQUIRED)
pkg_check_modules(_GRPC grpc REQUIRED)

set(CMAKE_PREFIX_PATH "$GRPC_DIR")
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_GRPC_GRPCPP grpc++)

# Proto file
message(STATUS "Specify a proto file and proto file path.")
get_filename_component(ex_proto "./proto/ex.proto" ABSOLUTE)
get_filename_component(ex_proto_path "${ex_proto}" PATH)

# Generated sources
message(STATUS "Genrate from the proto file.")
find_program(_PROTOBUF_PROTOC protoc REQUIRED)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin REQUIRED)
set(ex_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/ex.pb.cc")
set(ex_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/ex.pb.h")
set(ex_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/ex.grpc.pb.cc")
set(ex_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/ex.grpc.pb.h")
add_custom_command(
    OUTPUT "${ex_proto_srcs}" "${ex_proto_hdrs}" "${ex_grpc_srcs}" "${ex_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${ex_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${ex_proto}"
    DEPENDS "${ex_proto}")

# Include generated *.pb.h files
message(STATUS "Include the generated files.")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Create library: ex_grpc_proto 
message(STATUS "Add library: ex_grpc_proto.")
add_library(ex_grpc_proto
    ${ex_grpc_srcs}
    ${ex_grpc_hdrs}
    ${ex_proto_srcs}
    ${ex_proto_hdrs})
target_include_directories(ex_grpc_proto
    PRIVATE ${_PROTOBUF_INCLUDE_DIRS})
target_link_libraries(ex_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

# Target executables
message(STATUS "Make executable files.")
foreach(_target
    ex_server
    ex_client)
    add_executable(${_target} "${_target}.cc")
    target_include_directories(${_target}
        PRIVATE ${_GRPC_INCLUDE_DIRS})
    target_link_libraries(${_target}
        ex_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})
endforeach()