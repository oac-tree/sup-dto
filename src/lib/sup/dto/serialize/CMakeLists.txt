target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/byte_serializer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/i_writer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/scalar_to_bytes.cpp
        ${CMAKE_CURRENT_LIST_DIR}/writer_serializer.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
