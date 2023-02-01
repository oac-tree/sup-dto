cmake_minimum_required(VERSION 3.5)

project(sup-dto-project VERSION 0.1.0)

option(COVERAGE "Generate unit test coverage information" OFF)
option(SUP_DTO_EXPORT_BUILDTREE "Export build tree in /home/user/.cmake registry" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../cmake/module)
include(configuration)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic")
if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fno-inline --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(lib)

include(installation)
