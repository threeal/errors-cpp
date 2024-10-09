find_package(CDeps 0.1.0 REQUIRED)

cdeps_download_package(
  FixFormat github.com/threeal/FixFormat.cmake v${FixFormat_FIND_VERSION})

cdeps_build_package(FixFormat)
cdeps_install_package(FixFormat)

# TODO: Hardcode the version because FixFormat.cmake has an inconsistent version.
include(CMakeFindDependencyMacro)
find_dependency(FixFormat 1.1.0 CONFIG
  PATHS ${FixFormat_INSTALL_DIR}/lib/cmake NO_DEFAULT_PATH)
