cmake_minimum_required(VERSION 3.16)

if (NOT DEFINED _FOO)
	message("In ${CMAKE_CURRENT_BINARY_DIR} _FOO is not defined.")
else()
	message("In ${CMAKE_CURRENT_BINARY_DIR}, _FOO is ${_FOO}")
endif()

set(_BAR "../dummy.txt" PARENT_SCOPE)

message(STATUS "curr src dir: \t${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "curr bin dir: \t${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "src dir: \t\t${CMAKE_SOURCE_DIR}")
message(STATUS "bin dir: \t\t${CMAKE_BINARY_DIR}")