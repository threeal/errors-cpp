include(CPM)
cpmaddpackage(gh:threeal/FixFormat.cmake@${FixFormat_FIND_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FixFormat REQUIRED_VARS FixFormat.cmake_ADDED)

list(PREPEND CMAKE_MODULE_PATH ${FixFormat_SOURCE_DIR}/cmake)
