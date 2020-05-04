#pragma once


#include <doctest/doctest.h>
#include <chineseroom/fixed_string.hpp>


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
