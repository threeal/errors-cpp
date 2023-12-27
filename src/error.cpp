#include <errors/error.hpp>

namespace errors {

Error::Error(const std::shared_ptr<const std::string>& message_ptr) : message_ptr(message_ptr) {}

std::string_view Error::message() const {
  if (!message_ptr) return "no error";
  return *message_ptr;
}

Error::operator bool() const {
  return (bool)message_ptr;
}

std::ostream& operator<<(std::ostream& os, const errors::Error& err) {
  return os << "error: " << err.message();
}

Error make(const char* msg) {
  return Error(std::make_shared<const std::string>(msg));
}

const Error& nil() {
  static const Error err(nullptr);
  return err;
}

}  // namespace error
