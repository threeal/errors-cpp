find_package(CDeps 0.1.0 REQUIRED)

cdeps_download_package(Catch2 github.com/catchorg/Catch2 v${Catch2_FIND_VERSION})
cdeps_build_package(Catch2)
cdeps_install_package(Catch2)

include(CMakeFindDependencyMacro)
find_dependency(Catch2 ${Catch2_FIND_VERSION} CONFIG
  PATHS ${Catch2_INSTALL_DIR}/lib/cmake NO_DEFAULT_PATH)
