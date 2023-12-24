#pragma once

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

  Error(const std::shared_ptr<const std::string>& message_ptr);

 public:
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

  friend Error make(const std::string& msg);

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
};

/**
 * @brief Creates a new error object with the given message.
 * @param msg The error message.
 * @return A new error object.
 */
Error make(const std::string& msg);

}  // namespace error
