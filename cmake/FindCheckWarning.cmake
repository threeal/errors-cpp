include(CPM)
cpmaddpackage(gh:threeal/CheckWarning.cmake@${CheckWarning_FIND_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CheckWarning REQUIRED_VARS CheckWarning.cmake_ADDED)
