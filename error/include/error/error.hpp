#pragma once

#include <fmt/core.h>

#include <exception>
#include <memory>
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
   * @brief Returns the explanatory string.
   * @return Pointer to a null-terminated string with explanatory information.
   */
  const char* what() const noexcept override;
};

/**
 * @brief Alias for a shared pointer to the `Error` class.
 */
using ErrorPtr = std::shared_ptr<Error>;

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

}  // namespace error
