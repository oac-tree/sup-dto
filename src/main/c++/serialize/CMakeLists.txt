target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnySerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeSerializeStack.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
