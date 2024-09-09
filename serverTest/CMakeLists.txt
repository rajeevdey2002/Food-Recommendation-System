cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
 
# Enable testing
enable_testing()
 
# Find the GTest and GMock packages
find_package(GTest CONFIG REQUIRED)
 
# Find all the headers in the server/include directory and its subdirectories
file(GLOB_RECURSE SERVER_HEADERS ${CMAKE_SOURCE_DIR}/server/include/*.h)
 
# Find all the source files in the server/src directory and its subdirectories
file(GLOB_RECURSE SERVER_SOURCES ${CMAKE_SOURCE_DIR}/server/src/*.cpp)
 
# Find all the headers in the tests/include directory and its subdirectories
file(GLOB_RECURSE TEST_HEADERS ${CMAKE_SOURCE_DIR}/serverTest/include/*.h)
 
# Find all the source files in the tests/src directory and its subdirectories
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/serverTest/src/*.cpp)
 
# Extract directories from SERVER_HEADERS and TEST_HEADERS
set(SERVER_INCLUDE_DIRS "")
set(TEST_INCLUDE_DIRS "")
foreach(header IN LISTS SERVER_HEADERS)
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND SERVER_INCLUDE_DIRS ${dir})
endforeach()
 
foreach(header IN LISTS TEST_HEADERS)
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND TEST_INCLUDE_DIRS ${dir})
endforeach()
 
# Remove duplicate directories
list(REMOVE_DUPLICATES SERVER_INCLUDE_DIRS)
list(REMOVE_DUPLICATES TEST_INCLUDE_DIRS)
 
# Add the test executable, including server and test sources
add_executable(server_tests ${SERVER_SOURCES} ${TEST_SOURCES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find packages
find_package(mysqlcppconn REQUIRED)
find_package(Threads REQUIRED)

# Link against math library
target_link_libraries(server_tests PRIVATE m)

# Link against libraries using keywords
target_link_libraries(server_tests PRIVATE mysqlcppconn::mysqlcppconn ${CMAKE_THREAD_LIBS_INIT})
 
# Link the test executable with GTest and GMock
target_link_libraries(server_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(server_tests)
 
# Include all directories where the headers are located
target_include_directories(server_tests PRIVATE ${SERVER_INCLUDE_DIRS} ${TEST_INCLUDE_DIRS})
 
# Add the test executable to ctest
add_test(NAME server_tests COMMAND server_tests)
 
# Optionally, display the included directories for debugging
message("Server include directories: ${SERVER_INCLUDE_DIRS}")
message("Test include directories: ${TEST_INCLUDE_DIRS}")