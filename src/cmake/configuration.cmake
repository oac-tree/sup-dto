# Settings of CMake project

include(GNUInstallDirs)
include(CTest)

get_filename_component(SUP_DTO_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

set(LIBVERSION ${CMAKE_PROJECT_VERSION})
set(LIBSOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()
