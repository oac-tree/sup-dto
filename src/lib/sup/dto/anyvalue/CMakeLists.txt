target_sources(sup-dto-obj
    PRIVATE
    any_functor.cpp
    anytype_compare_node.cpp
    anytype_copy_node.cpp
    anytype_from_anyvalue_node.cpp
    anytype_helper.cpp
    anytype_registry.cpp
    anytype.cpp
    anyvalue_compare_node.cpp
    anyvalue_convert_node.cpp
    anyvalue_copy_node.cpp
    anyvalue_exceptions.cpp
    anyvalue_from_anytype_node.cpp
    anyvalue_helper.cpp
    anyvalue_operations_utils.cpp
    anyvalue_operations.cpp
    anyvalue.cpp
    array_type_data.cpp
    array_value_data.cpp
    basic_scalar_types.cpp
    empty_type_data.cpp
    empty_value_data.cpp
    field_utils.cpp
    i_type_data.cpp
    i_value_data.cpp
    scalar_type_data.cpp
    scalar_value_data_base.cpp
    struct_type_data.cpp
    struct_value_data.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
