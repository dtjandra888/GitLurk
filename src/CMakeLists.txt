
add_subdirectory(client)
add_subdirectory(types)

add_executable(gitlurk
    main.cpp
)

target_link_libraries(gitlurk
    PRIVATE
        client
        types
)
