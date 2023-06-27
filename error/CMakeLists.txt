cmake_minimum_required(VERSION 3.0)

project(error)

include(cmake/CPM.cmake)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")
  set(SUPPORT_TESTING TRUE)
  set(CHECK_WARNINGS TRUE)
endif()

if(SUPPORT_TESTING AND BUILD_TESTING)
  enable_testing()

  # Import Catch2 as the main testing framework.
  cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

  # Test coverage is not supported on MSVC.
  if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
  endif()
endif()

cpmaddpackage("gh:fmtlib/fmt#10.0.0")

add_library(error src/error.cpp)
target_include_directories(error PUBLIC include)
target_link_libraries(error PUBLIC fmt)

if(SUPPORT_TESTING AND BUILD_TESTING)
  add_executable(error_test test/error_test.cpp)
  target_link_libraries(error_test PRIVATE error Catch2::Catch2WithMain)
  catch_discover_tests(error_test)
endif()

set(TARGETS error error_test)
foreach(TARGET IN LISTS TARGETS)
  # Statically analyze code by checking for warnings.
  if(CHECK_WARNINGS)
    if(MSVC)
      target_compile_options(${TARGET} PRIVATE /WX /permissive- /W4 /w14640 /EHsc)
    else()
      target_compile_options(${TARGET} PRIVATE -Werror -Wall -Wextra -Wnon-virtual-dtor -Wpedantic)
    endif()
  endif()
endforeach()
