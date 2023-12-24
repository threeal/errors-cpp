#include <catch2/catch_test_macros.hpp>
#include <errors/error.hpp>
#include <sstream>

TEST_CASE("Error Construction") {
  const errors::Error err = errors::make("unknown error");
  REQUIRE(err.message() == "unknown error");
}

TEST_CASE("Error Printing Using OStream") {
  const auto err = errors::make("unknown error");
  const auto ss = std::stringstream() << err;
  REQUIRE(ss.str() == "error: unknown error");
}
