find_package(Python REQUIRED)

message(STATUS "Installing Python dependencies")
execute_process(
  COMMAND ${Python_EXECUTABLE} -m pip install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
  RESULT_VARIABLE RES
  ERROR_VARIABLE ERR
  OUTPUT_QUIET
)
if(NOT RES EQUAL 0 )
  message(FATAL_ERROR "Failed to install Python dependencies:\n${ERR}")
endif()

get_target_property(errors_docs_BINARY_DIR errors_docs BINARY_DIR)
get_target_property(errors_format_docs_BINARY_DIR errors_format_docs BINARY_DIR)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
  COMMAND ${Python_EXECUTABLE} -m sphinx -b html ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/html -W --keep-going
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/conf.py
    ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
    ${errors_docs_BINARY_DIR}/errors_docs.stamp
    ${errors_format_docs_BINARY_DIR}/errors_format_docs.stamp
)

add_custom_target(docs ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)
add_dependencies(docs errors_docs errors_format_docs)
