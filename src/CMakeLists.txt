
add_subdirectory(types)
add_subdirectory(client)
add_subdirectory(aggregator)

add_executable(gitlurk
    main.cpp
)

target_link_libraries(gitlurk
    PRIVATE
        types
        client
        aggregator
)
