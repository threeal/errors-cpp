# A function that creates XML documentation with the specified target name.
function(add_xml_docs targetName)
  # Try to find Doxygen
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    # Configure Doxygen to generate XML documentation
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_XML YES)

    # Generate Doxygen documentation
    doxygen_add_docs(${targetName} ${ARGN} ALL)
  else()
    message(WARNING "Could not found Doxygen!")
  endif()
endfunction()
