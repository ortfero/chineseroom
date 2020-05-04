#pragma once



#include <doctest/doctest.h>
#include <chineseroom/wildcards.hpp>


TEST_CASE("checking wildcards") {
  REQUIRE(chineseroom::has_wildcards("test*test"));
  REQUIRE(chineseroom::has_wildcards("test?test"));
  REQUIRE(chineseroom::has_wildcards("!test"));
  REQUIRE(!chineseroom::has_wildcards("test!test"));
  REQUIRE(!chineseroom::has_wildcards("testtest"));
}



TEST_CASE("pattern matching") {
  REQUIRE(chineseroom::matched("ab?ba", "abcba"));
  REQUIRE(chineseroom::matched("ab*ba", "abcdefba"));
  REQUIRE(chineseroom::matched("!ab?ba", "abba"));
  REQUIRE(chineseroom::matched("!ab*ba", "abcdefa"));
  REQUIRE(chineseroom::matched_list({"ab*ba", "!abcdefba"}, "abba"));
  REQUIRE(!chineseroom::matched("ab?ba", "abba"));
  REQUIRE(!chineseroom::matched("ab*ba", "abcdefa"));
  REQUIRE(!chineseroom::matched_list(std::string{"ab*ba,!abcdefba"}, "abcdefba"));
}
