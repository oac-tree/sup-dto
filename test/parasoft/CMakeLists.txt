if(NOT COA_PARASOFT_INTEGRATION)
  return()
endif()

message(STATUS "Configuring Parasoft integration")

if(NOT PARASOFT_DIR)
  if(NOT CODAC_FOUND)
    message(FATAL_ERROR "Parasoft install location is unknown, set PARASOFT_DIR to specify one")
  endif()

  # Default to CODAC parasoft installation location in /opt
  set(PARASOFT_DIR /opt/parasoft CACHE PATH "Parasoft install location")
endif()

# Append parasoft cmake integration location to module path
list(APPEND CMAKE_MODULE_PATH "${PARASOFT_DIR}/cpptest/integration/cmake")

# Enable parasoft project generation
set(CPPTEST_PROJECT ON)

# Include Parasoft integration module
include(cpptest-project)

# Add parasoft project for sup-dto-obj-target
# This generates the build time information needed by Parasoft for analysis
cpptest_add_executable(sup-dto-cpptest
  CPPTEST_PROJECT_LOC ${CMAKE_CURRENT_BINARY_DIR}
  CPPTEST_PROJECT_FOLDERS sup-dto-obj=${CMAKE_SOURCE_DIR}/src/lib/sup/dto
  TARGETS sup-dto-obj
)
get_target_property(SUP_DTO_INCLUDE_DIRECTORIES sup-dto-obj INCLUDE_DIRECTORIES)
target_include_directories(sup-dto-cpptest PUBLIC ${SUP_DTO_INCLUDE_DIRECTORIES})
