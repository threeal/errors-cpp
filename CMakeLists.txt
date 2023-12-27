cmake_minimum_required(VERSION 3.12)

project(errors)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(NOT_SUBPROJECT TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Initialize CPM.cmake
include(cmake/CPM.cmake)

# Build the main library
add_library(errors src/error.cpp)
target_include_directories(errors PUBLIC include)

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
    cpmaddpackage("gh:catchorg/Catch2@3.5.0")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

    # Append the main library properties instead of linking the library.
    get_target_property(errors_SOURCES errors SOURCES)
    get_target_property(errors_INCLUDES errors INCLUDE_DIRECTORIES)

    # Build tests for the main library
    add_executable(errors_test test/error_test.cpp ${errors_SOURCES})
    target_include_directories(errors_test PRIVATE ${errors_INCLUDES})
    target_link_libraries(errors_test PRIVATE Catch2::Catch2WithMain)

    # Enable support to check for test coverage
    if(NOT MSVC)
      target_compile_options(errors_test PRIVATE --coverage -O0 -fno-exceptions)
      target_link_options(errors_test PRIVATE --coverage)

      get_target_property(errors_test_SOURCES errors_test SOURCES)
      foreach(SOURCE ${errors_test_SOURCES})
        set(GCDA ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/errors_test.dir/${SOURCE}.gcda)
        add_custom_command(
          TARGET errors_test PRE_LINK
          COMMAND ${CMAKE_COMMAND} -E rm -f ${GCDA}
        )
      endforeach()
    endif()

    catch_discover_tests(errors_test)
  endif()

  # Build XML documentation
  if(BUILD_DOCS)
    include(cmake/add_xml_docs.cmake)
    add_xml_docs(errors_docs include/errors/error.hpp)
  endif()

  if(BUILD_EXAMPLES)
    add_subdirectory(examples)
  endif()
endif()

add_subdirectory(components)
