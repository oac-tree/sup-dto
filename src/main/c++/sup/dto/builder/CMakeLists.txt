# Files to build AnyValue in stepwise manner

target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/abstract_anyvalue_buildnode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_composer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_buildnodes.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_buildnode_utils.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
