
cmake_minimum_required(VERSION 3.10)
project(gitlurk)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(gitlurk
    src/main.cpp
    src/https_client.cpp
    src/github_client.cpp
)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

target_compile_options(gitlurk
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(gitlurk
    PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)
