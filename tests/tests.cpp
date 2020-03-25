#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chineseroom/chineseroom.hpp>



SCENARIO("Fixed string") {
 
  
  GIVEN("Constructed by default") {
    
    chineseroom::string target;
    
    THEN("Should be empty") {
      REQUIRE(target.empty());
    }
    THEN("Should has size 0") {
      REQUIRE(target.size() == 0);
      REQUIRE(target.length() == 0);
    }
  }


  
  GIVEN("Constructed from literal") {
    
    chineseroom::string target("test");
    
    THEN("Should be non-empty") {
      REQUIRE(!target.empty());
    }
    THEN("Should has size as literal") {
      REQUIRE(target.size() == sizeof("test") - 1);
      REQUIRE(target.length() == sizeof("test") - 1);
    }
  }
}



SCENARIO("Splitting string") {
  GIVEN("String '1,2,,3,'") {
    auto const splitted = chineseroom::split(std::string{"1,2,,3,"}, ',');
    THEN("Should be splitted to {'1', '2', '3'}") {
      REQUIRE(splitted.size() == 3);
      REQUIRE(splitted[0] == "1");
      REQUIRE(splitted[1] == "2");
      REQUIRE(splitted[2] == "3");
    }
  }
  GIVEN("String '1,2,,3,'") {
    auto const splitted = chineseroom::split_strictly(std::string{"1,2,,3,"}, ',');
    THEN("Should be strictly splitted to {'1', '2', '', '3', ''}") {
      REQUIRE(splitted.size() == 5);
      REQUIRE(splitted[0] == "1");
      REQUIRE(splitted[1] == "2");
      REQUIRE(splitted[2] == "");
      REQUIRE(splitted[3] == "3");
      REQUIRE(splitted[4] == "");
    }
  }
}



SCENARIO("Pattern matching") {

  GIVEN("String with wildcards") {
    THEN("Should be reported") {
      REQUIRE(chineseroom::has_wildcards("test*test"));
      REQUIRE(chineseroom::has_wildcards("test?test"));
    }
  }

  GIVEN("String without wildcards") {
    THEN("Should not be reported") {
      REQUIRE(!chineseroom::has_wildcards("testtest"));
    }
  }

  GIVEN("Single matched pattern") {
    THEN("Should be matched") {
      REQUIRE(chineseroom::matched("ab?ba", "abcba"));
      REQUIRE(chineseroom::matched("ab*ba", "abcdefba"));
      REQUIRE(chineseroom::matched("!ab?ba", "abba"));
      REQUIRE(chineseroom::matched("!ab*ba", "abcdefa"));
      REQUIRE(chineseroom::matched_list({"ab*ba", "!abcdefba"}, "abba"));
    }
  }

  GIVEN("Single unmatched pattern") {
    THEN("Should be unmatched") {
      REQUIRE(!chineseroom::matched("ab?ba", "abba"));
      REQUIRE(!chineseroom::matched("ab*ba", "abcdefa"));
      REQUIRE(!chineseroom::matched_list(std::string{"ab*ba,!abcdefba"}, "abcdefba"));
    }
  }
}
