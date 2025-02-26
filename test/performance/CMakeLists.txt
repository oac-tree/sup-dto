add_executable(sup-dto-performance-tests)

set_target_properties(sup-dto-performance-tests PROPERTIES OUTPUT_NAME "performance-tests")
set_target_properties(sup-dto-performance-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY})

target_sources(sup-dto-performance-tests
  PRIVATE
    main.cpp
    performance.cpp
)

target_link_libraries(sup-dto-performance-tests
  PRIVATE
    sup-dto-shared
)

