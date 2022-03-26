cmake_minimum_required(VERSION 3.16)
project(proj1)

set(_foo "./dummy.txt")

message("In ${CMAKE_CURRENT_BINARY_DIR}, _FOO is defined: ${_FOO}")

add_subdirectory(foo)
add_subdirectory(bar)