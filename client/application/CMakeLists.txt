add_library(application src/Application.cpp)

target_include_directories(application PUBLIC inc)

target_include_directories(application PUBLIC ../serverConnection/inc)

target_include_directories(application PUBLIC ../utils/inc)

target_include_directories(application PUBLIC ../authentication/inc)

target_include_directories(application PUBLIC ../chef/inc)

target_include_directories(application PUBLIC ../admin/inc)

target_include_directories(application PUBLIC ../employee/inc)

target_link_libraries(application PUBLIC serverConnection util auth admin chef employee)
