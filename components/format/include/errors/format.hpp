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
 */
template <typename... T>
Error format(fmt::format_string<T...> fmt, T&&... args);

}  // namespace errors

template <> struct fmt::formatter<errors::Error> : ostream_formatter {};

#include "format.ipp"
