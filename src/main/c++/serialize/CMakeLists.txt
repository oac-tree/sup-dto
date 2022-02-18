target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArraySerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ByteSerializer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreateAnySerializeNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScalarToBytes.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
