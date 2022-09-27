add_executable(unit-tests)

configure_file(${CMAKE_CURRENT_LIST_DIR}/test_config.h.in ${SUP_DTO_AUTOGEN_DIR}/test_config.h @ONLY)

target_sources(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/anytype_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anytype_json_parse_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anytype_json_serialize_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anytype_registry_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anytype_serialize_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_equality_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_exceptions_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_field_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_json_parse_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_json_serialize_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_serialize_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/anyvalue_ctype_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/arraytype_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/arrayvalue_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/integertype_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/integervalue_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/json_file_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/scalar_conversion_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/scalartype_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/scalarvalue_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/structuredtype_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/structuredvalue_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/test_serializers.cpp
)

target_include_directories(unit-tests
    PRIVATE
        ${SUP_DTO_AUTOGEN_DIR}
)

find_package(GTest REQUIRED)

target_link_libraries(unit-tests
    PRIVATE
        GTest::GTest
        GTest::Main
        gmock
        sup-dto-shared
)
