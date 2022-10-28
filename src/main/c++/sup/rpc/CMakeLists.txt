target_sources(sup-rpc
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/protocol_result.cpp
        ${CMAKE_CURRENT_LIST_DIR}/protocol_rpc_client.cpp
        ${CMAKE_CURRENT_LIST_DIR}/protocol_rpc_server.cpp
        ${CMAKE_CURRENT_LIST_DIR}/protocol_rpc.cpp
        ${CMAKE_CURRENT_LIST_DIR}/protocol.cpp
        ${CMAKE_CURRENT_LIST_DIR}/rpc_exceptions.cpp
)

target_include_directories(sup-rpc
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
