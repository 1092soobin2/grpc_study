cmake_minimum_required(VERSION 3.16)

if (NOT DEFINED _BAR)
	message("In ${CMAKE_CURRENT_BINARY_DIR} _BAR is not defined.")
else()
	message("In ${CMAKE_CURRENT_BINARY_DIR}, _BAR is ${_BAR}")
endif()
