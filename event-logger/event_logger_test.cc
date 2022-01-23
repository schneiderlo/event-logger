#include <catch2/catch.hpp>

#include "event-logger/event_logger.h"


TEST_CASE("Pad a string to the left", "[Formatting][Pad][left]")
{
  std::string src("true");
  sl::internal::pad_to_size_left(src, 2);
  REQUIRE(src == "true");
  sl::internal::pad_to_size_left(src, 6);
  REQUIRE(src == "  true");
  sl::internal::pad_to_size_left(src, 8);
  REQUIRE(src == "    true");
}

TEST_CASE("Pad a string to the right", "[Formatting][Pad][Right]")
{
  std::string src("true");
  sl::internal::pad_to_size_right(src, 2);
  REQUIRE(src == "true");
  sl::internal::pad_to_size_right(src, 6);
  REQUIRE(src == "true  ");
  sl::internal::pad_to_size_right(src, 8);
  REQUIRE(src == "true    ");
}

TEST_CASE("Pad a vector of strings", "[Formatting][Pad][Right]")
{
  std::vector<std::string> values {
    "This is it",
    "is",
    "a",
    "test"
  };
  const std::vector<std::string> ground_truth {
    "This is it",
    "is        ",
    "a         ",
    "test      "
  };
  sl::internal::pad_to_max_size_right(values);
  for (size_t i = 0; i != values.size(); i++) {
    REQUIRE(values[i] == ground_truth[i]);
  }
}
