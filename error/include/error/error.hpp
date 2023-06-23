#pragma once

#include <fmt/core.h>

#include <exception>
#include <memory>
#include <string>
#include <utility>

namespace error {

/**
 * @brief A class that represents error information.
 */
class Error : public std::exception {
 private:
  std::string message; /**< The error message. */

 public:
  /**
   * @brief Constructs a new error with the given format for the message.
   * @tparam T Variadic template parameter pack for format arguments.
   * @param fmt A format string for the message.
   * @param args Format arguments.
   */
  template <typename... T>
  Error(fmt::format_string<T...> fmt, T&&... args)
      : message(fmt::format(fmt, std::forward<T>(args)...)) {}

  /**
   * @brief Returns the explanatory string.
   * @return Pointer to a null-terminated string with explanatory information.
   */
  const char* what() const noexcept override;

  /**
   * @brief Checks if the error message matches the given string.
   * @param str A string to be matched.
   * @return True if it matches, false otherwise.
   */
  bool matches(const std::string& str) const noexcept;
};

/**
 * @brief Alias for a shared pointer to the `Error` class.
 */
using ErrorPtr = std::shared_ptr<Error>;

/**
 * @brief Creates a new error pointer with the given format for the message.
 * @tparam T Variadic template parameter pack for format arguments.
 * @param fmt A format string for the message.
 * @param args Format arguments.
 * @return Shared pointer to a new error.
 */
template <typename... T>
ErrorPtr make(fmt::format_string<T...> fmt, T&&... args) {
  return std::make_shared<Error>(fmt, std::forward<T>(args)...);
}

}  // namespace error
