#include <errors/error.hpp>
#include <fstream>
#include <iostream>

errors::Error read_file(const char* filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    return errors::make("failed to open file");
  }

  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
  }

  return errors::nil();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
    return 1;
  }

  const auto err = read_file(argv[1]);
  if (err) {
    std::cerr << err << std::endl;
    return 1;
  }

  return 0;
}
