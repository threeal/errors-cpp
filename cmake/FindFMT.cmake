include(CPM)
cpmaddpackage("gh:fmtlib/fmt#${FMT_FIND_VERSION}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FMT REQUIRED_VARS fmt_ADDED)
