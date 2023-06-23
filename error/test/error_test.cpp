#include <catch2/catch_test_macros.hpp>
#include <error/error.hpp>
#include <string>

TEST_CASE("Error Construction") {
  const error::Error err("unknown error");
  REQUIRE(err.message == "unknown error");
}

TEST_CASE("Error Construction With Formatting") {
  const error::Error err = error::format("HTTP error {}", 404);
  REQUIRE(err.message == "HTTP error 404");
}

TEST_CASE("Error Throwing and Catching") {
  SECTION("Catch as error::Error") {
    try {
      throw error::Error("unknown error");
    } catch (const error::Error& err) {
      REQUIRE(err.message == "unknown error");
    } catch (...) {
      FAIL("Expected to be caught as error::Error");
    }
  }

  SECTION("Catch as std::exception") {
    try {
      throw error::Error("unknown error");
    } catch (const std::exception& e) {
      REQUIRE(std::string("unknown error") == e.what());
    } catch (...) {
      FAIL("Expected to be caught as std::exception");
    }
  }
}
