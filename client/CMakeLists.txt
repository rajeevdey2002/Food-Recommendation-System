Cmake_minimum_required(VERSION 3.22.1)

project("RecommendationEngine")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(a.out Main.cpp)
target_link_libraries(a.out util serverConnection auth chef admin employee application)
add_subdirectory(utils)
add_subdirectory(serverConnection)
add_subdirectory(authentication)
add_subdirectory(chef)
add_subdirectory(admin)
add_subdirectory(employee)
add_subdirectory(application)