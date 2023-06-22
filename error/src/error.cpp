#include <error/error.hpp>

namespace error {

Error::Error(const char* message) : message(message) {}

const char* Error::what() const noexcept { return message.c_str(); }

}  // namespace error
