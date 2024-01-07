cmake_minimum_required(VERSION 3.23)

project(
  Errors
  VERSION 1.0.0
  DESCRIPTION "A C++ package that provides utilities for error handling ."
  HOMEPAGE_URL https://github.com/threeal/errors-cpp
  LANGUAGES CXX
)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(NOT_SUBPROJECT TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Initialize CPM.cmake
include(CPM)

# Build the main library
add_library(errors src/error.cpp)
target_sources(
  errors PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/errors/error.hpp
)

# Check if this project is the main project
if(NOT_SUBPROJECT)
  option(BUILD_DOCS "Enable documentations build" OFF)
  option(BUILD_EXAMPLES "Enable examples build" OFF)

  # Statically analyze code by checking for warnings
  cpmaddpackage(gh:threeal/CheckWarning.cmake@2.0.1)
  add_check_warning()

  # Import Format.cmake to format source code
  cpmaddpackage(
    GITHUB_REPOSITORY TheLartians/Format.cmake
    VERSION 1.8.0
    OPTIONS "FORMAT_SKIP_CMAKE ON"
  )

  if(BUILD_TESTING)
    enable_testing()

    # Import Catch2 as the main testing framework
    cpmaddpackage(gh:catchorg/Catch2@3.5.1)
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

  if(BUILD_DOCS)
    include(GenerateDocs)
    target_generate_xml_docs(errors)
  endif()
endif()

add_subdirectory(components)

if(NOT_SUBPROJECT AND BUILD_DOCS)
  add_subdirectory(docs)
endif()

if(NOT_SUBPROJECT AND BUILD_EXAMPLES)
  add_subdirectory(examples)
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
