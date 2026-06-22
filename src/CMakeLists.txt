
add_subdirectory(types)
add_subdirectory(client)

add_executable(gitlurk
    main.cpp
)

target_link_libraries(gitlurk
    PRIVATE
        client
        types
)
