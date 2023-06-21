#include <catch2/catch_test_macros.hpp>
#include <error/error.hpp>
#include <string>

TEST_CASE("Constructs an error") {
  const error::Error err("unknown error");
  const std::string expected("unknown error");
  REQUIRE(expected.compare(err.what()) == 0);
}
