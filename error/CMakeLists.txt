cmake_minimum_required(VERSION 3.0)

project(error)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive- /W4 /w14640 /EHsc")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -Wpedantic")
endif()

set(CMAKE_CXX_STANDARD 11)

include(cmake/CPM.cmake)
cpmaddpackage("gh:fmtlib/fmt#10.0.0")

add_library(error src/error.cpp)
target_include_directories(error PUBLIC include)
target_link_libraries(error PUBLIC fmt)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")

  if(BUILD_TESTING)
    enable_testing()

    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
    include("${Catch2_SOURCE_DIR}/extras/Catch.cmake")

    if(NOT MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
    endif()

    add_executable(error_test test/error_test.cpp)
    target_link_libraries(error_test PRIVATE error Catch2::Catch2WithMain)
    catch_discover_tests(error_test)
  endif()
endif()
