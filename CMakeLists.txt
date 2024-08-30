cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project("cafeteria" CXX)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/server")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/client")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/serverTest")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/clientTest")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)