
cmake_minimum_required(VERSION 3.10)
project(github-activity)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(github-activity
    src/main.cpp
    src/https_client.cpp
)
find_package(CURL REQUIRED)
target_link_libraries(main CURL::libcurl)
