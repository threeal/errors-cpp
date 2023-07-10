# A function that generates XML documentation from the specified source files.
function(add_xml_docs TARGET_NAME)
  # Try to install Doxygen if not found
  find_program(DOXYGEN_PROGRAM doxygen)
  if(NOT DOXYGEN_PROGRAM)
    find_program(APT_GET_PROGRAM apt-get)
    if(APT_GET_PROGRAM)
      message(STATUS "Doxygen could not be found, installing...")
      execute_process(COMMAND ${APT_GET_PROGRAM} install -y doxygen)
    endif()

    find_program(BREW_PROGRAM brew)
    if(BREW_PROGRAM)
      message(STATUS "Doxygen could not be found, installing...")
      execute_process(COMMAND ${BREW_PROGRAM} install doxygen)
    endif()
  endif()

  # Try to find Doxygen
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    # Configure Doxygen to generate XML documentation
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_XML YES)
    set(DOXYGEN_XML_OUTPUT ${TARGET_NAME})

    # Generate XML documentation for the target
    doxygen_add_docs(${TARGET_NAME} ${ARGN} USE_STAMP_FILE)
  endif()
endfunction()
