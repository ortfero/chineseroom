#pragma once


#include <doctest/doctest.h>
#include <chineseroom/split.hpp>

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

