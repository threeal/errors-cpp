include(CPM)
cpmaddpackage(gh:threeal/CheckWarning.cmake@${CheckWarning_FIND_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CheckWarning REQUIRED_VARS CheckWarning.cmake_ADDED)

list(PREPEND CMAKE_MODULE_PATH ${CheckWarning_SOURCE_DIR}/cmake)
