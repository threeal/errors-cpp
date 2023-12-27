#include <algorithm>
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

Error make(std::string_view msg) {
  auto c_msg = new char[msg.size() + 1];
  msg.copy(c_msg, msg.size());
  c_msg[msg.size()] = 0;
  return Error(std::shared_ptr<const char[]>(c_msg));
}

const Error& nil() {
  static const Error err(nullptr);
  return err;
}

}  // namespace error
