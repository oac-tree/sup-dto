if(NOT COA_BUILD_TESTS)
  return()
endif()

set(SUP_DTO_AUTOGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/autogen)
file(MAKE_DIRECTORY ${SUP_DTO_AUTOGEN_DIR})

find_package(benchmark QUIET)
# Print the benchmark found message
set(BENCHMARK_MESSAGE "Could NOT find Google Benchmark, skipping benchmark tests")
if(benchmark_FOUND)
  set(BENCHMARK_MESSAGE "Found Google Benchmark: ${benchmark_DIR} (found version \"${benchmark_VERSION}\")")
endif()
find_package_message(benchmark "${BENCHMARK_MESSAGE}" "[${BENCHMARK_MESSAGE}]")

add_subdirectory(unit)
add_subdirectory(performance)
if(benchmark_FOUND)
  add_subdirectory(benchmark)
endif()
add_subdirectory(parasoft)

file(WRITE ${TEST_OUTPUT_DIRECTORY}/test.sh
"#!/bin/bash
" ${TEST_OUTPUT_DIRECTORY} "/unit-tests \"$@\"
exit $?
")

configure_file(${TEST_OUTPUT_DIRECTORY}/test.sh ${TEST_OUTPUT_DIRECTORY}/test.sh
               FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
