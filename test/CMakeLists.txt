if(NOT COA_BUILD_TESTS)
  return()
endif()

set(SUP_DTO_AUTOGEN_DIR ${CMAKE_BINARY_DIR}/autogen)
file(MAKE_DIRECTORY ${SUP_DTO_AUTOGEN_DIR})

add_subdirectory(unit)
add_subdirectory(performance)
add_subdirectory(parasoft)

file(WRITE ${TEST_OUTPUT_DIRECTORY}/test.sh
"#!/bin/bash
" ${TEST_OUTPUT_DIRECTORY} "/unit-tests \"$@\"
exit $?
")

configure_file(${TEST_OUTPUT_DIRECTORY}/test.sh ${TEST_OUTPUT_DIRECTORY}/test.sh
               FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
