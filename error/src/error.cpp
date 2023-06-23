#include <error/error.hpp>

namespace error {

Error::Error(const std::string& msg) : message(msg) {}

const char* Error::what() const noexcept { return message.c_str(); }

}  // namespace error
