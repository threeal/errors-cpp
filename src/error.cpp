#include <cstring>
#include <errors/error.hpp>

namespace errors {

Error::Error(const std::shared_ptr<const char[]>& message_ptr) : message_ptr(message_ptr) {}

std::string_view Error::message() const {
  if (!message_ptr) return "no error";
  return message_ptr.get();
}

Error::operator bool() const {
  return (bool)message_ptr;
}

std::ostream& operator<<(std::ostream& os, const errors::Error& err) {
  return os << "error: " << err.message();
}

Error make(const char* msg) {
  auto msg_copy = new char[std::strlen(msg)];
  std::strcpy(msg_copy, msg);
  return Error(std::shared_ptr<const char[]>(msg_copy));
}

const Error& nil() {
  static const Error err(nullptr);
  return err;
}

}  // namespace error
