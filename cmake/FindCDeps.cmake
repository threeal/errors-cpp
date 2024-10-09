file(
  DOWNLOAD https://raw.githubusercontent.com/threeal/CDeps.cmake/d8c37677d9717738dd930005518cf1082c09eb71/cmake/CDeps.cmake
    ${CMAKE_BINARY_DIR}/cmake/CDeps.cmake
  EXPECTED_MD5 ab7516ba32bd687525f5d13bb349bf96)
include(${CMAKE_BINARY_DIR}/cmake/CDeps.cmake)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  CDeps REQUIRED_VARS CDEPS_VERSION VERSION_VAR CDEPS_VERSION)
