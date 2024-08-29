cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("cafeteria" CXX)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/server")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/client")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)