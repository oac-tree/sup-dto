target_sources(sup-rpc
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/protocol_result.cpp
        ${CMAKE_CURRENT_LIST_DIR}/protocol.cpp
)

target_include_directories(sup-rpc
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
