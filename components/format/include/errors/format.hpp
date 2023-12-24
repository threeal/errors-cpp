#pragma once

#include <errors/error.hpp>
#include <fmt/core.h>

namespace errors {

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

}  // namespace errors

template <>
struct fmt::formatter<errors::Error> {
  format_parse_context::iterator parse(format_parse_context& ctx) const;
  format_context::iterator format(const errors::Error& err,
                                  format_context& ctx) const;
};
