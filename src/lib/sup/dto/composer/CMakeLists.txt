# Files to build AnyValue in stepwise manner

target_sources(sup-dto-obj
    PRIVATE
    abstract_composer_component.cpp
    anyvalue_composer.cpp
    anyvalue_composer_components.cpp
    anyvalue_composer_helper.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
