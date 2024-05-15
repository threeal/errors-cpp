cpmaddpackage("gh:fmtlib/fmt#10.2.1")

add_custom_target(examples)

add_executable(example_print_hex print_hex.cpp)
target_link_libraries(example_print_hex PRIVATE errors)
add_dependencies(examples example_print_hex)

add_executable(example_read_file read_file.cpp)
target_link_libraries(example_read_file PRIVATE errors fmt)
add_dependencies(examples example_read_file)
