#include <errors/error.hpp>
#include <iostream>

errors::Error print_hex(const char* number_str) {
  int number = std::atoi(number_str);
  if (number == 0) {
    return errors::make("is not a number");
  }

  std::cout << std::hex << number << std::endl;
  return errors::nil();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <number>" << std::endl;
    return 1;
  }

  const auto err = print_hex(argv[1]);
  if (err) {
    std::cerr << err << std::endl;
    return 1;
  }

  return 0;
}
