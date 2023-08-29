target_sources(sup-dto-obj
  PRIVATE
    binary_serialization_functions.cpp
    binary_serializer.cpp
    ctype_serializer.cpp
    i_writer.cpp
    scalar_to_bytes.cpp
    writer_serializer.cpp
)

target_include_directories(sup-dto-obj
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
