#pragma once

#include <fmt/core.h>

#include <exception>
#include <ostream>
#include <string>
#include <utility>

namespace error {

/**
 * @brief Represents error information.
 */
struct Error : public std::exception {
  std::string message; /**< The error message. */

  /**
   * @brief Constructs a new error object with the given message.
   * @param msg An error message.
   */
  Error(const std::string& msg);

  /**
   * @brief Writes the string representation of an error object to the given
   * output stream.
   * @param os The output stream.
   * @param err The error object.
   * @return The output stream.
   *
   * This operator allows an error object to be printed to the output stream
   * using the << operator. The error message will be written to the output
   * stream.
   *
   * @code{.cpp}
   * const error::Error err("unknown error");
   *
   * // Print "error: unknown error"
   * std::cout << err << std::endl;
   * @endcode
   */
  friend std::ostream& operator<<(std::ostream& os, const error::Error& err);

  /**
   * @brief Returns the explanatory string.
   * @return Pointer to a null-terminated string with explanatory information.
   */
  const char* what() const noexcept override;
};

/**
 * @brief Creates a new error object with a formatted message.
 * @tparam T Variadic template parameter pack for format arguments.
 * @param fmt A format string for the message.
 * @param args Format arguments.
 * @return A new error object.
 */
template <typename... T>
Error format(fmt::format_string<T...> fmt, T&&... args) {
  return Error(fmt::format(fmt, std::forward<T>(args)...));
}

/**
 * @brief Checks if two error objects are equal.
 * @param lhs The left-hand side error object.
 * @param rhs The right-hand side error object.
 * @return True if equal, false otherwise.
 */
bool operator==(const Error& lhs, const Error& rhs);

/**
 * @brief Checks if two error objects are not equal.
 * @param lhs The left-hand side error object.
 * @param rhs The right-hand side error object.
 * @return True if not equal, false otherwise.
 */
bool operator!=(const Error& lhs, const Error& rhs);

}  // namespace error