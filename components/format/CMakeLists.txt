cpmaddpackage("gh:fmtlib/fmt#10.2.1")

add_library(errors_format INTERFACE)
target_sources(
  errors_format PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/errors/format.hpp
)
target_link_libraries(errors_format INTERFACE errors fmt)

if(NOT SUBPROJECT AND BUILD_TESTING)
  # Append the main library properties instead of linking the library.
  get_target_property(errors_format_HEADER_DIRS errors_format HEADER_DIRS)
  get_target_property(errors_format_LIBRARIES errors_format INTERFACE_LINK_LIBRARIES)

  # Build tests for the main library
  add_executable(errors_format_test test/format_test.cpp)
  target_include_directories(errors_format_test PRIVATE ${errors_format_HEADER_DIRS})
  target_link_libraries(errors_format_test PRIVATE Catch2::Catch2WithMain ${errors_format_LIBRARIES})

  # Enable support to check for test coverage
  include(CheckCoverage)
  target_check_coverage(errors_format_test)

  catch_discover_tests(errors_format_test)
endif()

if(NOT SUBPROJECT AND BUILD_DOCS)
  target_generate_xml_docs(errors_format)
endif()
