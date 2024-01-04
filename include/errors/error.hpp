#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

// Prevent conflicting name with the nil macro in Objective-C.
// See: https://github.com/threeal/errors-cpp/issues/128
#undef nil

namespace errors {

/**
 * @brief Represents error information.
 *
 * Use this class as the return type for functions that may produce errors.
 * This class has two state: either it contains an error or not.
 * Use boolean operations to check whether an object contains an error or not.
 *
 * @code{.cpp}
 * errors::Error print_hex(const char* number_str) {
 *   int number = std::atoi(number_str);
 *   if (number_str[0] != '0' && number == 0) {
 *     return errors::make("is not a number");
 *   }
 *
 *   std::cout << std::hex << number << std::endl;
 *   return errors::nil();
 * }
 *
 * int main() {
 *   // Print "7b".
 *   auto err = print_hex("123");
 *   assert(!err);
 *
 *   // Error.
 *   err = print_hex("not a number");
 *   assert(err);
 * }
 * @endcode
 */
class [[nodiscard]] Error {
 private:
  std::shared_ptr<const char[]> msg_ptr;

  Error(const std::shared_ptr<const char[]>& msg_ptr);

 public:
  /**
   * @brief Returns the error message.
   * @returns The error message.
   *
   * Returns the error message as a string view.
   * If the object does not contain an error, it will return the string "no error" instead.
   *
   * @code{.cpp}
   * const auto err = errors::make("unknown error");
   * const auto no_err = errors::nil();
   *
   * // Print "unknown error, no error".
   * std::cout << err.message() << ", " << no_err.message() << std::endl;
   * @endcode
   */
  std::string_view message() const;

  /**
   * @brief Checks whether it contains an error or not.
   * @return `true` if it contains an error, otherwise `false`.
   *
   * @code{.cpp}
   * const auto err = errors::make("unknown error");
   * assert(err);
   *
   * const auto no_err = errors::nil();
   * assert(!no_err);
   * @endcode
   */
  explicit operator bool() const;

  friend Error make(std::string_view msg);
  friend const Error& nil();

  /**
   * @brief Writes the string representation of an error object to the given
   * output stream.
   * @param os The output stream.
   * @param err The error object.
   * @return The output stream.
   *
   * This operator allows an error object to be printed to the output stream using the << operator.
   * The error message will be written to the output stream.
   *
   * @code{.cpp}
   * const auto err = errors::make("unknown error");
   *
   * // Print "error: unknown error".
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
Error make(std::string_view msg);

/**
 * @brief Gets a constant reference of an empty error.
 * @return A constant reference of an empty error.
 */
const Error& nil();

}  // namespace error
