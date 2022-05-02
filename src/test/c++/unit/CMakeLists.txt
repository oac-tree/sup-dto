add_executable(unit-tests)

if(EXPLICIT_TEST_BUILD_DEPENDENCIES)
    add_dependencies(unit-tests sup-dto-shared)
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/TestConfig.h.in ${SUP_DTO_AUTOGEN_DIR}/TestConfig.h @ONLY)

target_sources(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyType-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeJSONParse-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeJSONSerialize-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeRegistry-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeSerialize-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValue-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueExceptions-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueJSONParse-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueJSONSerialize-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueSerialize-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AnyValueCType-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArrayType-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArrayValue-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IntegerType-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IntegerValue-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/JSONFile-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScalarConversion-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScalarType-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScalarValue-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StructuredType-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StructuredValue-tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TestSerializers.cpp
)

target_include_directories(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../../main/c++/include
        ${CMAKE_CURRENT_LIST_DIR}/../../../main/c++/anyvalue
        ${CMAKE_CURRENT_LIST_DIR}/../../../main/c++/parse
        ${SUP_DTO_AUTOGEN_DIR}
)

target_link_directories(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../../../target/lib
)

find_package(GTest REQUIRED)

target_link_libraries(unit-tests
    PRIVATE
        GTest::GTest
        GTest::Main
        gmock
        sup-dto
)
