cpmaddpackage("gh:fmtlib/fmt#11.0.2")

add_library(errors_format INTERFACE)
target_sources(
  errors_format PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/errors/format.hpp
)
target_link_libraries(errors_format INTERFACE errors fmt)

if(PROJECT_IS_TOP_LEVEL AND ERRORS_ENABLE_TESTS)
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

if(PROJECT_IS_TOP_LEVEL AND BUILD_DOCS)
  target_generate_xml_docs(errors_format)
endif()
