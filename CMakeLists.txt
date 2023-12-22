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
  option(BUILD_DOCS "Enable documentations build" OFF)

  # Import Format.cmake to format source code
  cpmaddpackage(
    GITHUB_REPOSITORY TheLartians/Format.cmake
    VERSION 1.8.0
    OPTIONS "FORMAT_SKIP_CMAKE ON"
  )

  if(BUILD_TESTING)
    enable_testing()

    # Import Catch2 as the main testing framework
    cpmaddpackage("gh:catchorg/Catch2@3.5.0")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

    # Append the main library properties instead of linking the library.
    get_target_property(errors_SOURCES errors SOURCES)
    get_target_property(errors_INCLUDES errors INCLUDE_DIRECTORIES)
    get_target_property(errors_LIBRARIES errors LINK_LIBRARIES)
    get_target_property(errors_FEATURES errors COMPILE_FEATURES)

    # Build tests for the main library
    add_executable(errors_test test/error_test.cpp ${errors_SOURCES})
    target_include_directories(errors_test PRIVATE ${errors_INCLUDES})
    target_link_libraries(errors_test PRIVATE Catch2::Catch2WithMain ${errors_LIBRARIES})
    target_compile_features(errors_test PRIVATE ${errors_FEATURES})

    # Enable support to check for test coverage
    if(NOT MSVC)
      target_compile_options(errors_test PRIVATE --coverage -O0)
      target_link_options(errors_test PRIVATE --coverage)
    endif()

    catch_discover_tests(errors_test)
  endif()

  # Get all targets in this directory
  get_property(TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)

  cpmaddpackage(gh:threeal/CheckWarning.cmake@1.1.0)
  foreach(TARGET IN LISTS TARGETS)
    # Statically analyze code by checking for warnings
    target_check_warning(${TARGET})
  endforeach()

  # Build XML documentation
  if(BUILD_DOCS)
    include(cmake/add_xml_docs.cmake)
    add_xml_docs(docs include/errors/error.hpp)
  endif()
endif()
