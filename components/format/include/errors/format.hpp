#pragma once

#include <errors/error.hpp>
#include <fmt/core.h>
#include <fmt/ostream.h>

namespace errors {

/**
 * @brief Creates a new error object with a formatted message.
 * @tparam T Variadic template parameter pack for format arguments.
 * @param fmt A format string for the message.
 * @param args Format arguments.
 * @return A new error object.
 *
 * Use this function to create a new error object with a formatted message.
 * Refer to <a href="https://fmt.dev/latest/syntax.html">fmtlib's formatting syntax</a>
 * for more information on formatting a message for the error object.
 *
 * @code{.cpp}
 * const int code = 404;
 * const auto err = errors::format("HTTP error {}", code);
 *
 * // Print "error: HTTP error 404".
 * fmt::format("{}\n", err)
 * @endcode
 */
template <typename... T>
Error format(fmt::format_string<T...> fmt, T&&... args);

}  // namespace errors

template <> struct fmt::formatter<errors::Error> : ostream_formatter {};

#include "format.ipp"
