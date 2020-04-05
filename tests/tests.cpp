#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <chineseroom/chineseroom.hpp>



TEST_CASE("fixed string constructed by default") {
  chineseroom::string target;
  REQUIRE(target.empty());
  REQUIRE(target.size() == 0);
  REQUIRE(target.length() == 0);
}



TEST_CASE("fixed string constructed from 'test'") {
  chineseroom::string target("test");
  REQUIRE(!target.empty());
  REQUIRE(target.size() == sizeof("test") - 1);
  REQUIRE(target.length() == sizeof("test") - 1);
}



TEST_CASE("splitting string '1,2,,3,'") {
  auto const splitted = chineseroom::split(std::string{"1,2,,3,"}, ',');
  REQUIRE(splitted.size() == 3);
  REQUIRE(splitted[0] == "1");
  REQUIRE(splitted[1] == "2");
  REQUIRE(splitted[2] == "3");
}



TEST_CASE("strictly splitting string '1,2,,3,'") {
  auto const splitted = chineseroom::split_strictly(std::string{"1,2,,3,"}, ',');
  REQUIRE(splitted.size() == 5);
  REQUIRE(splitted[0] == "1");
  REQUIRE(splitted[1] == "2");
  REQUIRE(splitted[2] == "");
  REQUIRE(splitted[3] == "3");
  REQUIRE(splitted[4] == "");
}



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
