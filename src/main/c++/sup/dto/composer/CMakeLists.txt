# Files to build AnyValue in stepwise manner

target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/abstract_composer_component.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_composer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_composer_components.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_composer_helper.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
