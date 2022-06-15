cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic")
if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_library(sup-dto-obj OBJECT)
set_property(TARGET sup-dto-obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(sup-dto-shared SHARED)
add_library(sup-dto-static STATIC)

add_subdirectory(sup)

target_include_directories(sup-dto-obj
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

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

install(FILES
        sup/dto/anytype.h
        sup/dto/anytype_helper.h
        sup/dto/anytype_registry.h
        sup/dto/anyvalue.h
        sup/dto/anyvalue_exceptions.h
        sup/dto/anyvalue_helper.h
        sup/dto/basic_scalar_types.h
        sup/dto/i_any_visitor.h
        DESTINATION include/sup/dto
)
