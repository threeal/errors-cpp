#include <catch2/catch_test_macros.hpp>
#include <error/error.hpp>
#include <string>

TEST_CASE("Error Construction") {
  SECTION("With one argument") {
    const error::Error err("unknown error");
    REQUIRE(std::string("unknown error") == err.what());
  }

  SECTION("With one or more arguments") {
    const error::Error err("HTTP error {}", 404);
    REQUIRE(std::string("HTTP error 404") == err.what());
  }
}

TEST_CASE("Error Throwing and Catching") {
  SECTION("Catch as error::Error") {
    try {
      throw error::Error("unknown error");
    } catch (const error::Error& err) {
      REQUIRE(std::string("unknown error") == err.what());
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
