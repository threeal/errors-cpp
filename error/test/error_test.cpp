#include <catch2/catch_test_macros.hpp>
#include <error/error.hpp>

TEST_CASE("test Error::what") {
  const error::Error err;
  const std::string expected("unknown error");
  REQUIRE(expected.compare(err.what()) == 0);
}
