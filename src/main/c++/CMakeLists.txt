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

add_library(sup-dto::sup-dto ALIAS sup-dto-shared) # alias for build-tree usage
add_library(sup-dto::sup-dto-static ALIAS sup-dto-static) # alias for build-tree usage

add_library(sup-rpc SHARED)
add_library(sup-dto::sup-rpc ALIAS sup-rpc) # alias for build-tree usage

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
    sup-dto-obj
    PUBLIC
)

target_include_directories(sup-dto-shared PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

set_target_properties(sup-dto-static PROPERTIES OUTPUT_NAME sup-dto)
target_link_libraries(sup-dto-static PRIVATE $<BUILD_INTERFACE:sup-dto-obj>)

target_include_directories(sup-dto-static PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

install(TARGETS sup-dto-shared EXPORT sup-dto-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-dto-shared PROPERTIES EXPORT_NAME sup-dto)
install(TARGETS sup-dto-static EXPORT sup-dto-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-dto-static PROPERTIES EXPORT_NAME sup-dto-static)

set_target_properties(sup-rpc PROPERTIES
  VERSION ${LIBVERSION}
  SOVERSION ${LIBSOVERSION}
  OUTPUT_NAME sup-rpc
)

target_link_libraries(sup-rpc
  PRIVATE
  sup-dto-shared
  PUBLIC
)

target_include_directories(sup-rpc PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

install(TARGETS sup-rpc EXPORT sup-dto-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
        sup/dto/anytype.h
        sup/dto/anytype_helper.h
        sup/dto/anytype_registry.h
        sup/dto/anyvalue.h
        sup/dto/anyvalue_exceptions.h
        sup/dto/anyvalue_helper.h
        sup/dto/anyvalue_composer.h
        sup/dto/basic_scalar_types.h
        sup/dto/any_functor.h
        sup/dto/i_any_visitor.h
        sup/dto/json_type_parser.h
        sup/dto/json_value_parser.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/dto)

install(FILES
        sup/rpc/protocol_result.h
        sup/rpc/protocol_rpc_client.h
        sup/rpc/protocol_rpc_server.h
        sup/rpc/protocol_rpc.h
        sup/rpc/protocol.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/rpc)
