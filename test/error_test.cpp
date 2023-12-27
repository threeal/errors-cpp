#include <catch2/catch_test_macros.hpp>
#include <errors/error.hpp>
#include <sstream>

TEST_CASE("Error Construction") {
  const auto err = errors::make("unknown error");
  REQUIRE(err);
  REQUIRE(err.message() == "unknown error");
}

TEST_CASE("Empty Error Construction") {
  const auto err = errors::nil();
  REQUIRE_FALSE(err);
  REQUIRE(err.message() == "no error");
}

TEST_CASE("Error Printing Using OStream") {
  const auto err = errors::make("unknown error");
  const auto ss = std::stringstream() << err;
  REQUIRE(ss.str() == "error: unknown error");
}
