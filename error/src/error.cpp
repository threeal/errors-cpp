#include <error/error.hpp>

namespace error {

std::ostream& operator<<(std::ostream& os, const error::Error& err) {
  return os << "error: " << err.what();
}

const char* Error::what() const noexcept { return message.c_str(); }

Error make(const std::string& msg) { return Error{.message = msg}; }

bool operator==(const Error& lhs, const Error& rhs) {
  return lhs.message == rhs.message;
}

bool operator!=(const Error& lhs, const Error& rhs) {
  return lhs.message != rhs.message;
}

}  // namespace error

namespace fmt {

format_parse_context::iterator formatter<error::Error>::parse(
    format_parse_context& ctx) const {
  return ctx.begin();
}

format_context::iterator formatter<error::Error>::format(
    const error::Error& err, format_context& ctx) const {
  return format_to(ctx.out(), "error: {}", err.what());
}

}  // namespace fmt
