add_executable(performance-tests)

if(EXPLICIT_TEST_BUILD_DEPENDENCIES)
    add_dependencies(performance-tests sup-dto-shared)
endif()

target_sources(performance-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/JSONPerformance.cpp
)

target_include_directories(performance-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../../main/c++
)

target_link_directories(performance-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../../../target/lib
)

find_package(GTest REQUIRED)

target_link_libraries(performance-tests
    PRIVATE
        sup-dto
)
