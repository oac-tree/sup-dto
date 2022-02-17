target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueHelper.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
