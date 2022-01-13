cmake_minimum_required(VERSION 3.5)

project(SUP-DTO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (DEFINED COVERAGE AND ${COVERAGE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_library(sup-dto-obj OBJECT)
set_property(TARGET sup-dto-obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(sup-dto-shared SHARED)
add_library(sup-dto-static STATIC)

add_subdirectory(anyvalue)
add_subdirectory(include)

set_target_properties(sup-dto-shared PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-dto
)

target_link_libraries(sup-dto-shared
    PRIVATE
    PUBLIC
        sup-dto-obj
    )

set_target_properties(sup-dto-static PROPERTIES
    OUTPUT_NAME sup-dto
)

target_link_libraries(sup-dto-static
    PRIVATE
    PUBLIC
        sup-dto-obj
)

install(TARGETS sup-dto-shared DESTINATION lib)
install(TARGETS sup-dto-static DESTINATION lib)
install(DIRECTORY include/ DESTINATION include
    FILES_MATCHING PATTERN "*.h")