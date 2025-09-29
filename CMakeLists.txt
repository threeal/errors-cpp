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

option(ERRORS_ENABLE_TESTS "Enable test targets.")

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_DOCS "Enable documentations build" OFF)
  option(BUILD_EXAMPLES "Enable examples build" OFF)

  if(ERRORS_ENABLE_TESTS)
    enable_testing()
  endif()
endif()

# Prefer system packages over the find modules provided by this project.
if(NOT DEFINED CMAKE_FIND_PACKAGE_PREFER_CONFIG)
  set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
endif()

if(PROJECT_IS_TOP_LEVEL)
  # Statically analyze code by checking for warnings
  find_package(CheckWarning 3.2.0 REQUIRED)
  add_check_warning(TREAT_WARNINGS_AS_ERRORS)
endif()

# Build the main library
add_library(errors src/error.cpp)
target_sources(
  errors PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/errors/error.hpp
)

if(PROJECT_IS_TOP_LEVEL AND ERRORS_ENABLE_TESTS)
  # Import Catch2 as the main testing framework
  find_package(Catch2 3.10.0 REQUIRED)
  include(Catch)

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

if(PROJECT_IS_TOP_LEVEL AND ERRORS_ENABLE_TESTS)
  # Enable automatic target formatting.
  find_package(FixFormat 1.1.1 REQUIRED)
  include(FixFormat)
  add_fix_format()
endif()

install(
  TARGETS errors errors_format fmt
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
