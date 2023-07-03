#include <fmt/core.h>

#include <catch2/catch_test_macros.hpp>
#include <error/error.hpp>
#include <sstream>
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

TEST_CASE("Error Comparison") {
  const auto err = error::Error("unknown error");
  const auto err_copy = err;
  CHECK(err == err_copy);
  CHECK_FALSE(err != err_copy);
  const auto other_err = error::Error("other error");
  CHECK_FALSE(err == other_err);
  CHECK(err != other_err);
}

TEST_CASE("Error Printing") {
  const error::Error err("unknown error");

  SECTION("Using ostream") {
    const auto ss = std::stringstream() << err;
    REQUIRE(ss.str() == "error: unknown error");
  }

  SECTION("Using fmtlib") {
    REQUIRE(fmt::format("{}", err) == "error: unknown error");
  }
}
