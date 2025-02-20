target_sources(sup-dto-obj
    PRIVATE
    any_visitornode.cpp
    array_visitornode.cpp
    create_any_visitornode.cpp
)

target_include_directories(sup-dto-obj
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)
