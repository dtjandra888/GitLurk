

add_library(aggregator
    event_aggregator.cpp
)

target_link_libraries(aggregator
    PUBLIC
        types
)

target_include_directories(aggregator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
