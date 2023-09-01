add_executable(unit-tests)

target_compile_features(unit-tests PRIVATE cxx_std_11)

configure_file(${CMAKE_CURRENT_LIST_DIR}/test_config.h.in ${SUP_DTO_AUTOGEN_DIR}/test_config.h @ONLY)

target_sources(unit-tests
  PRIVATE
    abstract_composer_component_tests.cpp
    anytype_builder_tests.cpp
    anytype_composer_components_tests.cpp
    anytype_composer_helper_tests.cpp
    anytype_field_tests.cpp
    anytype_json_serialize_tests.cpp
    anytype_registry_tests.cpp
    anytype_serialize_tests.cpp
    anytype_tests.cpp
    anyvalue_assign_tests.cpp
    anyvalue_builder_tests.cpp
    anyvalue_comparison_tests.cpp
    anyvalue_composer_components_tests.cpp
    anyvalue_composer_helper_tests.cpp
    anyvalue_composer_tests.cpp
    anyvalue_ctype_tests.cpp
    anyvalue_decrement_tests.cpp
    anyvalue_equality_tests.cpp
    anyvalue_exceptions_tests.cpp
    anyvalue_field_tests.cpp
    anyvalue_helper_tests.cpp
    anyvalue_increment_tests.cpp
    anyvalue_json_serialize_tests.cpp
    anyvalue_serialize_tests.cpp
    anyvalue_tests.cpp
    arraytype_tests.cpp
    arrayvalue_invariant_tests.cpp
    arrayvalue_tests.cpp
    binary_encoding_tests.cpp
    binary_parser_functions_tests.cpp
    binary_serialization_functions_tests.cpp
    binary_type_serialization_tests.cpp
    integertype_tests.cpp
    integervalue_tests.cpp
    json_file_tests.cpp
    json_type_parser_tests.cpp
    json_typed_value_parser_tests.cpp
    json_value_parser_tests.cpp
    scalar_conversion_tests.cpp
    scalartype_tests.cpp
    scalarvalue_tests.cpp
    structuredtype_tests.cpp
    structuredvalue_tests.cpp
    test_serializers.cpp
)

target_include_directories(unit-tests
  PRIVATE
  ${SUP_DTO_AUTOGEN_DIR}
)

find_package(GTest REQUIRED)

include(GoogleTest)

target_link_libraries(unit-tests
  PRIVATE
    GTest::GTest
    GTest::Main
    sup-dto-shared
)

set_target_properties(unit-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY})

gtest_discover_tests(unit-tests)
