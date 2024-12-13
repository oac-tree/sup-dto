target_sources(sup-dto-obj
  PRIVATE
    abstract_type_composer_component.cpp
    abstract_value_composer_component.cpp
    anytype_composer_components.cpp
    anytype_composer_helper.cpp
    anytype_composer.cpp
    anyvalue_composer_components.cpp
    anyvalue_composer_helper.cpp
    anyvalue_composer.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
