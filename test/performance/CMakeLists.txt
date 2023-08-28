add_executable(performance-tests)

target_compile_features(performance-tests PRIVATE cxx_std_11)

target_sources(performance-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/performance.cpp
)

target_link_libraries(performance-tests
    PRIVATE
    sup-dto-shared
)

set_target_properties(performance-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY})
