cmake_minimum_required(VERSION 3.0)

project(error)

# Import dependencies
include(cmake/CPM.cmake)
cpmaddpackage("gh:fmtlib/fmt#10.0.0")

# Build the main library
add_library(error src/error.cpp)
target_include_directories(error PUBLIC include)
target_link_libraries(error PUBLIC fmt)

# Check if this project is the main project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(CHECK_FORMAT "Enable source code formatting check" OFF)
  option(CHECK_WARNING "Enable static analysis warning check" OFF)

  # Import Format.cmake to format source code
  if(CHECK_FORMAT)
    cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")
    add_dependencies(error fix-format)
  endif()

  if(BUILD_TESTING)
    enable_testing()

    # Import Catch2 as the main testing framework
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

    # Build tests for the main library
    add_executable(error_test test/error_test.cpp)
    target_link_libraries(error_test PRIVATE error Catch2::Catch2WithMain)
    catch_discover_tests(error_test)
  endif()

  # Get all targets in this directory
  get_property(
    TARGETS
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY BUILDSYSTEM_TARGETS)

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
    if(BUILD_TESTING AND NOT MSVC)
      target_compile_options(${TARGET} PRIVATE --coverage -O0)
      target_link_options(${TARGET} PRIVATE --coverage)
    endif()
  endforeach()
endif()
