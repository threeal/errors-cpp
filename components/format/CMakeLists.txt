cpmaddpackage("gh:fmtlib/fmt#10.0.0")

add_library(errors_format src/format.cpp)
target_sources(
  errors_format PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/errors/format.hpp
)
target_link_libraries(errors_format PUBLIC errors fmt)

if(NOT_SUBPROJECT)
  if (BUILD_TESTING)
    # Append the main library properties instead of linking the library.
    get_target_property(errors_format_SOURCES errors_format SOURCES)
    get_target_property(errors_format_HEADER_DIRS errors_format HEADER_DIRS)
    get_target_property(errors_format_LIBRARIES errors_format LINK_LIBRARIES)

    # Build tests for the main library
    add_executable(errors_format_test test/format_test.cpp ${errors_format_SOURCES})
    target_include_directories(errors_format_test PRIVATE ${errors_format_HEADER_DIRS})
    target_link_libraries(errors_format_test PRIVATE Catch2::Catch2WithMain ${errors_format_LIBRARIES})

    # Enable support to check for test coverage
    if(NOT MSVC)
      target_compile_options(errors_format_test PRIVATE --coverage -O0 -fno-exceptions)
      target_link_options(errors_format_test PRIVATE --coverage)

      get_target_property(errors_format_test_SOURCES errors_format_test SOURCES)
      foreach(SOURCE ${errors_format_test_SOURCES})
        set(GCDA ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/errors_format_test.dir/${SOURCE}.gcda)
        add_custom_command(
          TARGET errors_format_test PRE_LINK
          COMMAND ${CMAKE_COMMAND} -E rm -f ${GCDA}
        )
      endforeach()
    endif()

    catch_discover_tests(errors_format_test)
  endif()

  # Build XML documentation
  if(BUILD_DOCS)
    add_xml_docs(errors_format_docs include/errors/format.hpp)
  endif()
endif()
