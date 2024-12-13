add_library(sup-dto-obj OBJECT)
set_property(TARGET sup-dto-obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(sup-dto-shared SHARED)
add_library(sup-dto-static STATIC)

add_library(sup-dto::sup-dto ALIAS sup-dto-shared) # alias for build-tree usage
add_library(sup-dto::sup-dto-static ALIAS sup-dto-static) # alias for build-tree usage

target_include_directories(sup-dto-obj PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>
)

set_target_properties(sup-dto-shared PROPERTIES
  VERSION ${LIBVERSION}
  SOVERSION ${LIBSOVERSION}
  OUTPUT_NAME sup-dto
)

target_link_libraries(sup-dto-shared
  PRIVATE
    sup-dto-obj
)

target_include_directories(sup-dto-shared PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>)

set_target_properties(sup-dto-static PROPERTIES
  OUTPUT_NAME sup-dto
)

target_link_libraries(sup-dto-static
  PRIVATE
    $<BUILD_INTERFACE:sup-dto-obj>
)

target_include_directories(sup-dto-static PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>)

add_subdirectory(anyvalue)
add_subdirectory(composer)
add_subdirectory(json)
add_subdirectory(low_level)
add_subdirectory(parse)
add_subdirectory(serialize)
add_subdirectory(visit)

# -- Installation --

install(TARGETS sup-dto-shared EXPORT sup-dto-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-dto-shared PROPERTIES EXPORT_NAME sup-dto)
install(TARGETS sup-dto-static EXPORT sup-dto-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-dto-static PROPERTIES EXPORT_NAME sup-dto-static)

install(FILES
  any_functor.h
  anytype_composer.h
  anytype_helper.h
  anytype_registry.h
  anytype.h
  anyvalue_composer.h
  anyvalue_exceptions.h
  anyvalue_helper.h
  anyvalue_operations.h
  anyvalue.h
  basic_scalar_types.h
  i_any_visitor.h
  json_type_parser.h
  json_value_parser.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/dto
)
