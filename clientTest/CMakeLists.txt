cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
 
# Enable testing
enable_testing()
 
# Find the GTest and GMock packages
find_package(GTest CONFIG REQUIRED)
 
# Find all the headers in the client/include directory and its subdirectories
file(GLOB_RECURSE CLIENT_HEADERS ${CMAKE_SOURCE_DIR}/client/include/*.h)
 
# Find all the source files in the client/src directory and its subdirectories
file(GLOB_RECURSE CLIENT_SOURCES ${CMAKE_SOURCE_DIR}/client/src/*.cpp)
 
# Find all the headers in the tests/include directory and its subdirectories
file(GLOB_RECURSE TEST_HEADERS ${CMAKE_SOURCE_DIR}/clientTest/include/*.h)
 
# Find all the source files in the tests/src directory and its subdirectories
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/clientTest/src/*.cpp)
 
# Extract directories from CLIENT_HEADERS and TEST_HEADERS
set(CLIENT_INCLUDE_DIRS "")
set(TEST_INCLUDE_DIRS "")
foreach(header IN LISTS CLIENT_HEADERS)
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND CLIENT_INCLUDE_DIRS ${dir})
endforeach()
 
foreach(header IN LISTS TEST_HEADERS)
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND TEST_INCLUDE_DIRS ${dir})
endforeach()
 
# Remove duplicate directories
list(REMOVE_DUPLICATES CLIENT_INCLUDE_DIRS)
list(REMOVE_DUPLICATES TEST_INCLUDE_DIRS)
 
# Add the test executable, including client and test sources
add_executable(client_tests ${CLIENT_SOURCES} ${TEST_SOURCES})
 
# Link the test executable with GTest and GMock
target_link_libraries(client_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(client_tests)
 
# Include all directories where the headers are located
target_include_directories(client_tests PRIVATE ${CLIENT_INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
 
# Add the test executable to ctest
add_test(NAME client_tests COMMAND client_tests)
 
# Optionally, display the included directories for debugging
message("Server include directories: ${CLIENT_INCLUDE_DIRS}")
message("Test include directories: ${TEST_INCLUDE_DIRS}")