#pragma once


#include <doctest/doctest.h>
#include <chineseroom/replace.hpp>

TEST_CASE("replace/1") {
  std::string target("test test");
  REQUIRE(chineseroom::replace(target, ' ', '_') == "test_test");
}



TEST_CASE("replace/2") {
  std::string target;
  REQUIRE(chineseroom::replace(target, ' ', '_') == "");
}
