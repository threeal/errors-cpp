#include <fmt/core.h>

#include <catch2/catch_test_macros.hpp>
#include <errors/format.hpp>

TEST_CASE("Error Construction With Formatting") {
  const errors::Error err = errors::format("HTTP error {}", 404);
  REQUIRE(err.message() == "HTTP error 404");
}

TEST_CASE("Error Printing Using fmtlib") {
  const auto err = errors::make("unknown error");
  REQUIRE(fmt::format("{}", err) == "error: unknown error");
}
