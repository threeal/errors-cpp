#include <error/error.hpp>

namespace error {

Error::Error(const std::string& msg) : message(msg) {}

const char* Error::what() const noexcept { return message.c_str(); }

bool operator==(const Error& lhs, const Error& rhs) {
  return lhs.message == rhs.message;
}

bool operator!=(const Error& lhs, const Error& rhs) {
  return lhs.message != rhs.message;
}

}  // namespace error
