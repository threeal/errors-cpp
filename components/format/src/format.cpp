#include <errors/format.hpp>

namespace fmt {

format_parse_context::iterator formatter<errors::Error>::parse(
    format_parse_context& ctx) const {
  return ctx.begin();
}

format_context::iterator formatter<errors::Error>::format(
    const errors::Error& err, format_context& ctx) const {
  return format_to(ctx.out(), "error: {}", err.message());
}

}  // namespace fmt
