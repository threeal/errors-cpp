#include <errors/error.hpp>
#include <iostream>

// Prints the hexadecimal representation of the given number string.
errors::Error print_hex(const char* number_str) {
  int number = std::atoi(number_str);
  if (number_str[0] != '0' && number == 0) {
    // The given string is not a number, return an error.
    return errors::make("is not a number");
  }

  // Print the number and return nil.
  std::cout << std::hex << number << std::endl;
  return errors::nil();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <number>" << std::endl;
    return 1;
  }

  // Call the function and handle the error.
  const auto err = print_hex(argv[1]);
  if (err) {
    std::cerr << err << std::endl;
    return 1;
  }

  return 0;
}
