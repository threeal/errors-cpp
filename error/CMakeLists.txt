cmake_minimum_required(VERSION 3.0)

project(error)

include(cmake/CPM.cmake)

# Check if this project is the main project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(SUPPORT_TESTING TRUE)
  set(CHECK_WARNINGS TRUE)

  # Import Format.cmake to format source code
  cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")
endif()

if(SUPPORT_TESTING AND BUILD_TESTING)
  enable_testing()

  # Import Catch2 as the main testing framework
  cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

  # Test coverage is not supported on MSVC
  if(NOT MSVC)
    set(CHECK_COVERAGE TRUE)
  endif()
endif()

# Import dependencies
cpmaddpackage("gh:fmtlib/fmt#10.0.0")

# Build the main library
add_library(error src/error.cpp)
target_include_directories(error PUBLIC include)
target_link_libraries(error PUBLIC fmt)

if(SUPPORT_TESTING AND BUILD_TESTING)
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
  if(CHECK_WARNINGS)
    if(MSVC)
      target_compile_options(${TARGET} PRIVATE /WX /permissive- /W4 /w14640 /EHsc)
    else()
      target_compile_options(${TARGET} PRIVATE -Werror -Wall -Wextra -Wnon-virtual-dtor -Wpedantic)
    endif()
  endif()

  # Enable support to check for test coverage
  if(CHECK_COVERAGE)
    target_compile_options(${TARGET} PRIVATE --coverage -O0)
    target_link_options(${TARGET} PRIVATE --coverage)
  endif()
endforeach()
