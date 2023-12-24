#include <fmt/core.h>

#include <catch2/catch_test_macros.hpp>
#include <errors/error.hpp>
#include <sstream>
#include <string>

TEST_CASE("Error Construction") {
  const errors::Error err = errors::make("unknown error");
  REQUIRE(err.message() == "unknown error");
}

TEST_CASE("Error Construction With Formatting") {
  const errors::Error err = errors::format("HTTP error {}", 404);
  REQUIRE(err.message() == "HTTP error 404");
}

TEST_CASE("Error Printing") {
  const auto err = errors::make("unknown error");

  SECTION("Using ostream") {
    const auto ss = std::stringstream() << err;
    REQUIRE(ss.str() == "error: unknown error");
  }

  SECTION("Using fmtlib") {
    REQUIRE(fmt::format("{}", err) == "error: unknown error");
  }
}
