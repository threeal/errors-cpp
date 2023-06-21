#pragma once

#include <exception>

namespace error {

/**
 * @brief A struct that represents error information.
 */
struct Error : public std::exception {
  /**
   * @brief Returns the explanatory string.
   * @return Pointer to a null-terminated string with explanatory information.
   */
  const char* what() const noexcept override;
};

}  // namespace error
