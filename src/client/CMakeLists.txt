
add_library(client
    github_client.cpp
    https_client.cpp
)

target_link_libraries(client
    PUBLIC
        CURL::libcurl
        nlohmann_json::nlohmann_json
        types
)

target_include_directories(client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
