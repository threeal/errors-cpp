# A function that generates XML documentation from the specified target.
function(target_generate_xml_docs TARGET)
  # Try to find Doxygen
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    # Configure Doxygen to generate XML documentation
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_XML YES)

    # Get include directories of the target
    foreach(PROP INCLUDE_DIRECTORIES INTERFACE_INCLUDE_DIRECTORIES)
      get_target_property(TARGET_INCLUDE_DIRS ${TARGET} ${PROP})
      list(APPEND INCLUDE_DIRS ${TARGET_INCLUDE_DIRS})
    endforeach()

    # Generate XML documentation from the target
    doxygen_add_docs(${TARGET}_docs ${INCLUDE_DIRS})
    add_dependencies(${TARGET} ${TARGET}_docs)
  else()
    message(WARNING "Could not found Doxygen!")
  endif()
endfunction()
