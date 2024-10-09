add_executable(performance-tests)

target_sources(performance-tests
  PRIVATE
    main.cpp
    performance.cpp
)

target_link_libraries(performance-tests
  PRIVATE
    sup-dto-shared
)

set_target_properties(performance-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY})
