cmake_minimum_required(VERSION 3.0)

project(errors)

# Import dependencies
include(cmake/CPM.cmake)
cpmaddpackage("gh:fmtlib/fmt#10.0.0")

# Build the main library
add_library(errors src/error.cpp)
target_include_directories(errors PUBLIC include)
target_link_libraries(errors PUBLIC fmt)
target_compile_features(errors PRIVATE cxx_std_20)

# Check if this project is the main project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(CHECK_FORMAT "Enable source code formatting check" OFF)
  option(CHECK_WARNING "Enable static analysis warning check" OFF)
  option(CHECK_COVERAGE "Enable test coverage check" OFF)
  option(BUILD_DOCS "Enable documentations build" OFF)

  # Import Format.cmake to format source code
  if(CHECK_FORMAT)
    cpmaddpackage("gh:threeal/Format.cmake#auto-install-cmake-format")
    add_dependencies(errors fix-format)
  endif()

  if(BUILD_TESTING)
    enable_testing()

    # Import Catch2 as the main testing framework
    cpmaddpackage("gh:catchorg/Catch2@3.4.0")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

    # Build tests for the main library
    add_executable(errors_test test/error_test.cpp)
    target_link_libraries(errors_test PRIVATE errors Catch2::Catch2WithMain)
    catch_discover_tests(errors_test)
  endif()

  # Get all targets in this directory
  get_property(TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

  foreach(TARGET IN LISTS TARGETS)
    # Statically analyze code by checking for warnings
    if(CHECK_WARNING)
      if(MSVC)
        target_compile_options(${TARGET} PRIVATE /WX /permissive- /W4 /w14640 /EHsc)
      else()
        target_compile_options(${TARGET} PRIVATE -Werror -Wall -Wextra -Wnon-virtual-dtor -Wpedantic)
      endif()
    endif()

    # Enable support to check for test coverage
    if(BUILD_TESTING AND CHECK_COVERAGE AND NOT MSVC)
      target_compile_options(${TARGET} PRIVATE --coverage -O0)
      target_link_options(${TARGET} PRIVATE --coverage)
    endif()
  endforeach()

  # Build XML documentation
  if(BUILD_DOCS)
    include(cmake/add_xml_docs.cmake)
    add_xml_docs(docs include/error/error.hpp)
  endif()
endif()
