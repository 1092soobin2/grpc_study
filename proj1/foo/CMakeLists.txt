cmake_minimum_required(VERSION 3.16)

if (NOT DEFINED _FOO)
	message("In ${CMAKE_CURRENT_BINARY_DIR} _FOO is not defined.")
else()
	message("In ${CMAKE_CURRENT_BINARY_DIR}, _FOO is ${_FOO}")
endif()

set(_BAR "../dummy.txt" PARENT_SCOPE)