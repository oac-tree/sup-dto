target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ArrayVisitorNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreateAnyVisitorNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UnboundedArrayVisitorNode.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
