cpmaddpackage("gh:fmtlib/fmt#10.0.0")

add_library(errors_format src/format.cpp)
target_include_directories(errors_format PUBLIC include)
target_link_libraries(errors_format PUBLIC errors fmt)
target_compile_features(errors_format PRIVATE cxx_std_20)

if(NOT_SUBPROJECT)
  if (BUILD_TESTING)
    # Append the main library properties instead of linking the library.
    get_target_property(errors_format_SOURCES errors_format SOURCES)
    get_target_property(errors_format_INCLUDES errors_format INCLUDE_DIRECTORIES)
    get_target_property(errors_format_LIBRARIES errors_format LINK_LIBRARIES)
    get_target_property(errors_format_FEATURES errors_format COMPILE_FEATURES)

    # Build tests for the main library
    add_executable(errors_format_test test/format_test.cpp ${errors_format_SOURCES})
    target_include_directories(errors_format_test PRIVATE ${errors_format_INCLUDES})
    target_link_libraries(errors_format_test PRIVATE Catch2::Catch2WithMain ${errors_format_LIBRARIES})
    target_compile_features(errors_format_test PRIVATE ${errors_format_FEATURES})

    # Enable support to check for test coverage
    if(NOT MSVC)
      target_compile_options(errors_format_test PRIVATE --coverage -O0 -fno-exceptions)
      target_link_options(errors_format_test PRIVATE --coverage)
    endif()

    catch_discover_tests(errors_format_test)
  endif()

  # Build XML documentation
  if(BUILD_DOCS)
    add_xml_docs(errors_format_docs include/errors/format.hpp)
  endif()
endif()
