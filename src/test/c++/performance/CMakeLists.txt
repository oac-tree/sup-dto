add_executable(performance-tests)

target_sources(performance-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/json_performance.cpp
)

target_link_libraries(performance-tests
    PRIVATE
    sup-dto-shared
)
