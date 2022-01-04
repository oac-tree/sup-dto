target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyType.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValue.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueExceptions.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EmptyTypeData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScalarTypeData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StructTypeData.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
