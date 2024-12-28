find_package(CDeps 0.1.0 REQUIRED)

cdeps_download_package(FMT github.com/fmtlib/fmt ${FMT_FIND_VERSION})
cdeps_build_package(FMT)
cdeps_install_package(FMT)

include(CMakeFindDependencyMacro)
find_dependency(FMT ${FMT_FIND_VERSION} CONFIG
  PATHS ${FMT_INSTALL_DIR}/lib/cmake NO_DEFAULT_PATH)
