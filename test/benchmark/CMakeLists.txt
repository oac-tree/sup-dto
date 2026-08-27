set(benchmark-tests sup-dto-benchmark-tests)

add_executable(${benchmark-tests})

set_target_properties(${benchmark-tests} PROPERTIES OUTPUT_NAME "benchmark-tests")
set_target_properties(${benchmark-tests} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY})

target_sources(${benchmark-tests}
  PRIVATE
    anytype_benchmark.cpp
    anyvalue_benchmark.cpp
    binary_benchmark.cpp
    json_benchmark.cpp
    main.cpp
    shape_fixtures.cpp
)

target_link_libraries(${benchmark-tests}
  PRIVATE
    benchmark::benchmark
    sup-dto-shared
)
