#include <error/error.hpp>

namespace error {

const char* Error::what() const noexcept { return "unknown error"; }

}  // namespace error
