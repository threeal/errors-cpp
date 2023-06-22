#include <error/error.hpp>

namespace error {

const char* Error::what() const noexcept { return message.c_str(); }

}  // namespace error
