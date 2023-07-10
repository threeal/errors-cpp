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
      if(NOT "${TARGET_INCLUDE_DIRS}" STREQUAL "TARGET_INCLUDE_DIRS-NOTFOUND")
        list(APPEND INCLUDE_DIRS ${TARGET_INCLUDE_DIRS})
      endif()
    endforeach()
    list(REMOVE_DUPLICATES INCLUDE_DIRS)

    # Get header files from the include directories
    foreach(DIR ${TARGET_INCLUDE_DIRS})
      file(GLOB_RECURSE FILES CONFIGURE_DEPENDS "${DIR}/*")
      list(APPEND HEADER_FILES ${FILES})
    endforeach()

    # Generate XML documentation for the target
    doxygen_add_docs(${TARGET}_docs ${HEADER_FILES} USE_STAMP_FILE)
    add_dependencies(${TARGET} ${TARGET}_docs)
  else()
    message(WARNING "Could not found Doxygen!")
  endif()
endfunction()
