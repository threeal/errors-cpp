# Function to generate an XML documentation of a specific target.
# Arguments:
#   - TARGET: The target for which to generate an XML documentation.
function(target_generate_xml_docs TARGET)
  find_package(Doxygen REQUIRED)

  # Configure Doxygen to generate an XML documentation.
  set(DOXYGEN_GENERATE_HTML NO)
  set(DOXYGEN_GENERATE_XML YES)
  set(DOXYGEN_XML_OUTPUT ${TARGET}_docs)

  get_target_property(TARGET_HEADER_SET ${TARGET} HEADER_SET)
  doxygen_add_docs(${TARGET}_docs ${TARGET_HEADER_SET} USE_STAMP_FILE)
endfunction()
