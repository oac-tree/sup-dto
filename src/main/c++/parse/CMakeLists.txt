target_sources(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnyTypeBuildNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IAnyBuildNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MemberTypeArrayBuildNode.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MemberTypeBuildNode.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
