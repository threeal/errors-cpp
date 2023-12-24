#include <errors/error.hpp>

namespace errors {

Error::Error(const std::shared_ptr<const std::string>& message_ptr) : message_ptr(message_ptr) {}

std::string Error::message() const {
  if (!message_ptr) return "no error";
  return *message_ptr;
}

std::ostream& operator<<(std::ostream& os, const errors::Error& err) {
  return os << "error: " << err.message();
}

Error make(const std::string& msg) {
  return Error(std::make_shared<const std::string>(msg));
}

}  // namespace error
