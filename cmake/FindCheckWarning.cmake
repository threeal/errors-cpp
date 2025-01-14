find_package(CDeps 0.1.0 REQUIRED)

cdeps_download_package(
  CheckWarning github.com/threeal/CheckWarning.cmake
  v${CheckWarning_FIND_VERSION})

cdeps_build_package(CheckWarning)
cdeps_install_package(CheckWarning)

include(CMakeFindDependencyMacro)
find_dependency(CheckWarning ${CheckWarning_FIND_VERSION} CONFIG
  PATHS ${CheckWarning_INSTALL_DIR}/lib/cmake NO_DEFAULT_PATH)
