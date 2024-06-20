cmake_minimum_required(VERSION 3.23)

project(
  Errors
  VERSION 1.0.0
  DESCRIPTION "A C++ package that provides utilities for error handling ."
  HOMEPAGE_URL https://github.com/threeal/errors-cpp
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_DOCS "Enable documentations build" OFF)
  option(BUILD_EXAMPLES "Enable examples build" OFF)

  if(BUILD_TESTING)
    enable_testing()
  endif()
endif()

# Initialize CPM.cmake
include(CPM)

if(PROJECT_IS_TOP_LEVEL)
  # Statically analyze code by checking for warnings
  cpmaddpackage(gh:threeal/CheckWarning.cmake@2.1.0)
  include(${CheckWarning_SOURCE_DIR}/cmake/CheckWarning.cmake)
  add_check_warning()
endif()

# Build the main library
add_library(errors src/error.cpp)
target_sources(
  errors PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/errors/error.hpp
)

if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
  # Import Catch2 as the main testing framework
  cpmaddpackage(gh:catchorg/Catch2@3.6.0)
  include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

  # Append the main library properties instead of linking the library.
  get_target_property(errors_SOURCES errors SOURCES)
  get_target_property(errors_HEADER_DIRS errors HEADER_DIRS)

  # Build tests for the main library
  add_executable(errors_test test/error_test.cpp ${errors_SOURCES})
  target_include_directories(errors_test PRIVATE ${errors_HEADER_DIRS})
  target_link_libraries(errors_test PRIVATE Catch2::Catch2WithMain)

  # Enable support to check for test coverage
  include(CheckCoverage)
  target_check_coverage(errors_test)

  catch_discover_tests(errors_test)
endif()

if(PROJECT_IS_TOP_LEVEL AND BUILD_DOCS)
  include(GenerateDocs)
  target_generate_xml_docs(errors)
endif()

add_subdirectory(components)

if(PROJECT_IS_TOP_LEVEL AND BUILD_DOCS)
  add_subdirectory(docs)
endif()

if(PROJECT_IS_TOP_LEVEL AND BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
  # Enable automatic target formatting.
  cpmaddpackage(gh:threeal/FixFormat.cmake@1.1.1)
  include(${FixFormat_SOURCE_DIR}/cmake/FixFormat.cmake)
  add_fix_format()
endif()

install(
  TARGETS errors errors_format
  EXPORT errors_targets
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  FILE_SET HEADERS
)

install(
  EXPORT errors_targets
  FILE ErrorsTargets.cmake
  NAMESPACE errors::
  DESTINATION lib/cmake/Errors
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ErrorsConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    cmake/ErrorsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ErrorsConfigVersion.cmake
  DESTINATION lib/cmake/Errors
)
