target_sources(sup-dto-obj
  PRIVATE
    binary_parser_functions.cpp
    binary_serialization_functions.cpp
    scalar_to_bytes.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
