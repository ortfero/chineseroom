#pragma once


#include <doctest/doctest.h>
#include <chineseroom/texter.hpp>



TEST_CASE("basic_texter::basic_texter") {
  chineseroom::std_texter target;
  REQUIRE(target.size() == 0);
  REQUIRE(target.empty());
  REQUIRE(target.data()[0] == '\0');
  REQUIRE(target.string().size() == 0);
  REQUIRE(target.string().empty());
  REQUIRE(target.string().data()[0] == '\0');
}


TEST_CASE("basic_texter::print(char)") {
  chineseroom::std_texter target;
  target << 'a';
  REQUIRE(target.string() == "a");
  target.print('x');
  REQUIRE(target.string() == "ax");
}


TEST_CASE("basic_texter::clear") {
  chineseroom::std_texter target;
  target << 'a';
  target.clear();
  REQUIRE(target.size() == 0);
  REQUIRE(target.empty());
  REQUIRE(target.data()[0] == '\0');
  REQUIRE(target.string().size() == 0);
  REQUIRE(target.string().empty());
  REQUIRE(target.string().data()[0] == '\0');
}


TEST_CASE("basic_texter::print(char[])") {
  chineseroom::std_texter target;
  target << "ok";
  REQUIRE(target.string() == "ok");
  target.print("ko");
  REQUIRE(target.string() == "okko");
}


