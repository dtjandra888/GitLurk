
cmake_minimum_required(VERSION 3.31)
project(gitlurk)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_subdirectory(src)
