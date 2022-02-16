target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeSerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeSerializeStack.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArrayTypeSerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EmptyTypeSerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MemberTypeSerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScalarTypeSerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StructTypeSerializeNode.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
