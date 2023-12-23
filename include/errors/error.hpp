#pragma once

#include <fmt/core.h>

#include <memory>
#include <ostream>
#include <string>
#include <utility>

namespace errors {

/**
 * @brief Represents error information.
 */
class Error {
 private:
  const std::shared_ptr<const std::string> message_ptr;

 public:
  Error(const std::shared_ptr<const std::string>& message_ptr);

  /**
   * @brief Returns the error message.
   *
   * @code{.cpp}
   * const auto err = errors::make("unknown error");
   *
   * // Print "unknown error"
   * std::cout << err << std::endl;
   * @endcode
   */
  std::string message() const;

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
   * const auto err = errors::make("unknown error");
   *
   * // Print "error: unknown error"
   * std::cout << err << std::endl;
   * @endcode
   */
  friend std::ostream& operator<<(std::ostream& os, const errors::Error& err);

  /**
   * @brief Checks if two error objects are equal.
   * @param lhs The left-hand side error object.
   * @param rhs The right-hand side error object.
   * @return True if equal, false otherwise.
   *
   * This operator allows the comparison of two error objects using the == operator.
   *
   * @code{.cpp}
   * const auto err = errors::make("unknown error");
   * const auto other_err = err;
   *
   * assert(err == other_err);
   * @endcode
   */
  friend bool operator==(const Error& lhs, const Error& rhs);

  /**
   * @brief Checks if two error objects are not equal.
   * @param lhs The left-hand side error object.
   * @param rhs The right-hand side error object.
   * @return True if not equal, false otherwise.
   *
   * This operator allows the comparison of two error objects using the != operator.
   *
   * @code{.cpp}
   * const auto err = errors::make("unknown error");
   * const auto other_err = errors::make("other error");
   *
   * assert(err != other_err);
   * @endcode
   */
  friend bool operator!=(const Error& lhs, const Error& rhs);
};

/**
 * @brief Creates a new error object with the given message.
 * @param msg The error message.
 * @return A new error object.
 */
Error make(const std::string& msg);

/**
 * @brief Creates a new error object with a formatted message.
 * @tparam T Variadic template parameter pack for format arguments.
 * @param fmt A format string for the message.
 * @param args Format arguments.
 * @return A new error object.
 */
template <typename... T>
Error format(fmt::format_string<T...> fmt, T&&... args) {
  return errors::make(fmt::format(fmt, std::forward<T>(args)...));
}

}  // namespace error

template <>
struct fmt::formatter<errors::Error> {
  format_parse_context::iterator parse(format_parse_context& ctx) const;
  format_context::iterator format(const errors::Error& err,
                                  format_context& ctx) const;
};
