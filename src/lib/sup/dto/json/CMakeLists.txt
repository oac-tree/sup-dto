target_sources(sup-dto-obj
    PRIVATE
    json_reader.cpp
    json_writer.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
