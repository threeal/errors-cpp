#include <errors/error.hpp>
#include <errors/format.hpp>
#include <fstream>

errors::Error read_file(const char* filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    return errors::format("failed to open `{}` ({})", filepath, file.rdstate());
  }

  std::string line;
  while (std::getline(file, line)) {
    fmt::print("{}\n", line);
  }

  return errors::nil();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fmt::print(stderr, "usage: {} <filepath>\n", argv[0]);
    return 1;
  }

  const auto err = read_file(argv[1]);
  if (err) {
    fmt::print(stderr, "{}\n", err);
    return 1;
  }

  return 0;
}
