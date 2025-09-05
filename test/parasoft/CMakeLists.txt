if(NOT COA_PARASOFT_INTEGRATION)
  return()
endif()

include(COASetupParasoft)

# Add parasoft project for sup-dto-obj-target
# This generates the build time information needed by Parasoft for analysis
cpptest_add_executable(sup-dto-cpptest
  CPPTEST_PROJECT_LOC ${CMAKE_CURRENT_BINARY_DIR}
  CPPTEST_PROJECT_FOLDERS
  sup-dto-obj=${CMAKE_SOURCE_DIR}/src/lib/sup/dto
  TARGETS sup-dto-obj
)
get_target_property(SUP_DTO_INCLUDE_DIRECTORIES sup-dto-obj INCLUDE_DIRECTORIES)
target_include_directories(sup-dto-cpptest PUBLIC ${SUP_DTO_INCLUDE_DIRECTORIES})
