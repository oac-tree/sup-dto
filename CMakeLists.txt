cmake_minimum_required(VERSION 3.5)

project(SUP-DTO-PROJECT VERSION 0.1.0)

option(COVERAGE "Generate unit test coverage information" FALSE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/src/cmake)
set(TARGET_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/target)
include(configuration)

add_subdirectory(src/main/c++)
add_subdirectory(src/test/c++)

include(installation)
