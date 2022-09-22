cmake_minimum_required(VERSION 3.5)

project(SUP-DTO-PROJECT VERSION 0.1.0)

option(COVERAGE "Generate unit test coverage information" OFF)
option(SUP_DTO_EXPORT_BUILDTREE "Export build tree in /home/user/.cmake registry" OFF)

set(TARGET_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../src/cmake)
include(configuration)

add_subdirectory(main/c++)
add_subdirectory(test/c++)

include(installation)
