#include <catch2/catch_test_macros.hpp>
#include <error/error.hpp>
#include <string>

TEST_CASE("Error Construction") {
  SECTION("With one argument") {
    const error::Error err("unknown error");
    REQUIRE(err.match("unknown error"));
  }

  SECTION("With one or more arguments") {
    const error::Error err("HTTP error {}", 404);
    REQUIRE(err.match("HTTP error 404"));
  }
}

TEST_CASE("Error Pointer Construction") {
  SECTION("With one argument") {
    const error::ErrorPtr err = error::make("unknown error");
    REQUIRE(err->match("unknown error"));
  }

  SECTION("With one or more arguments") {
    const error::ErrorPtr err = error::make("HTTP error {}", 404);
    REQUIRE(err->match("HTTP error 404"));
  }
}

TEST_CASE("Error Throwing and Catching") {
  SECTION("Catch as error::Error") {
    try {
      throw error::Error("unknown error");
    } catch (const error::Error& err) {
      REQUIRE(err.match("unknown error"));
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

TEST_CASE("Error Message Matching") {
  const error::Error err("unknown error");
  REQUIRE(err.match("unknown error"));
}
