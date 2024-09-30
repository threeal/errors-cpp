include(CPM)
cpmaddpackage(gh:catchorg/Catch2@${Catch2_FIND_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Catch2 REQUIRED_VARS Catch2_ADDED)

list(PREPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
