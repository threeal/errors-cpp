# A function that generates XML documentation from the specified source files.
function(add_xml_docs TARGET_NAME)
  # Try to find Doxygen
  find_package(Doxygen REQUIRED)

  # Configure Doxygen to generate XML documentation
  set(DOXYGEN_GENERATE_HTML NO)
  set(DOXYGEN_GENERATE_XML YES)
  set(DOXYGEN_XML_OUTPUT ${TARGET_NAME})

  # Generate XML documentation for the target
  doxygen_add_docs(${TARGET_NAME} ${ARGN} USE_STAMP_FILE)
endfunction()
