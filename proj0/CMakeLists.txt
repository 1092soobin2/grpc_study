cmake_minimum_required(VERSION 3.5.1)

project(proj0 C CXX)

message(STATUS "Using gRPC via add_subdirectory.")

# find_package(PkgConfig REQUIRED)
# pkg_check_modules(_PROTOBUF protobuf REQUIRED)
# pkg_check_modules(_GRPC grpc REQUIRED)

# add_subdirectory($ENV{HOME}/grpc ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)
# 상위 폴더에서 패치되어 있으면 패치 안 함.
if (NOT DEFINED _GRPC_GRPCPP) 
    message(STATUS "${CMAKE_CURRENT_BINARY_DIR}: Using gRPC via add_subdirectory (FetchContent).")
    include(FetchContent)
    FetchContent_Declare(
    grpc
    GIT_REPOSITORY https://github.com/grpc/grpc
    # when using gRPC, you will actually set this to an existing tag, such as
    # v1.25.0, v1.26.0 etc..
    # For the purpose of testing, we override the tag used to the commit
    # that's currently under test.
    GIT_TAG        v1.45.0)
    FetchContent_MakeAvailable(grpc)

    # Since FetchContent uses add_subdirectory under the hood, we can use
    # the grpc targets directly from this build.
    set(_PROTOBUF_LIBPROTOBUF libprotobuf)
    set(_REFLECTION grpc++_reflection)
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
    set(_GRPC_GRPCPP grpc++)
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

# set(CMAKE_PREFIX_PATH "${_GRPC_INCLUDE_DIRS}")
# set(_PROTOBUF_LIBPROTOBUF libprotobuf)
# set(_REFLECTION grpc++_reflection)
# set(_GRPC_GRPCPP grpc++)

# Proto file
get_filename_component(ex_proto "./proto/ex.proto" ABSOLUTE)
get_filename_component(ex_proto_path "${ex_proto}" PATH)

# Generated sources
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
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Create library: ex_grpc_proto 
add_library(ex_grpc_proto
    ${ex_grpc_srcs}
    ${ex_grpc_hdrs}
    ${ex_proto_srcs}
    ${ex_proto_hdrs})
target_link_libraries(ex_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBRARIES})
# Target executables
foreach(_target
    ex_server
    ex_client)
    add_executable(${_target} "${_target}.cc")
    # target_include_directories(${_target}
    #     PRIVATE ${_GRPC_INCLUDE_DIRS})
    target_link_libraries(${_target}
        ex_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBRARIES})
endforeach()