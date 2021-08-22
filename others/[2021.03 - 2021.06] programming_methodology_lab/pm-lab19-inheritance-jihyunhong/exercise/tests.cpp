#define CATCH_CONFIG_MAIN // defines main() automatically
#include "catch.hpp"
#include "inheritance.hpp" // student implementations

TEST_CASE("Ex1","[InheritanceTest]") {
  Beef beef{} ;
  REQUIRE("Beef" == beef.getName());
  REQUIRE("Barbeque" == beef.cook());
  REQUIRE("Bulgogi" == beef.cook2());
}
TEST_CASE("Ex2","[InheritanceTest]") {
  Pork pork{ };
  REQUIRE("Pork" == pork.getName());
  REQUIRE("Barbeque"== pork.cook());
  REQUIRE("Jokbal" == pork.cook2());
}
TEST_CASE("Ex3","[InheritanceTest]") {
  Chicken chicken{};
  REQUIRE("Chicken" == chicken.getName());
  REQUIRE("Barbeque"== chicken.cook());
  REQUIRE("Fried Chicken" == chicken.cook2());
}
