#pragma once

#include <exception>

namespace error {

/**
 * @brief A class that represents error information.
 */
class Error : public std::exception {
 private:
  const char* message; /**< The error message. */

 public:
  /**
   * @brief Constructs a new error with the given message.
   * @param message An error message.
   */
  Error(const char* message);

  /**
   * @brief Returns the explanatory string.
   * @return Pointer to a null-terminated string with explanatory information.
   */
  const char* what() const noexcept override;
};

}  // namespace error
