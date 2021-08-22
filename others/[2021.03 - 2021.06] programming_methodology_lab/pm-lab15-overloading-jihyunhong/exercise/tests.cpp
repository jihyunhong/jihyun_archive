#define CATCH_CONFIG_MAIN // defines main() automatically
#include "catch.hpp"

#include "double_vector.h" // student implementation

#include <string>
#include <sstream>


TEST_CASE("Test1", "[Rule of Three]") {
  DoubleVector vec1(5);
  vec1.Fill(3.0);

  DoubleVector vec2(vec1);
  vec1.Fill(10.0);
  // Test Copy Constructor
  REQUIRE((vec2.GetLength() == 5 &&
           vec2[0] == 3.0 && vec2[1] == 3.0 && vec2[2] == 3.0 &&
           vec2[3] == 3.0 && vec2[4] == 3.0));
  
//  double* vec1Old = nullptr;
  {
    DoubleVector vec1(5);
    vec1.Fill(3.0);

    DoubleVector vec3(5);
    vec3.Fill(2.0);
 //   double* vec3Old = &vec3[0];
    vec3 = vec1;
    vec1.Fill(10.0);
    // Test Assignment Operator
    REQUIRE((vec3.GetLength() == 5 &&
             vec3[0] == 3.0 && vec3[1] == 3.0 && vec3[2] == 3.0 &&
             vec3[3] == 3.0 && vec3[4] == 3.0));
    // Test assignment memory leak
 //   REQUIRE_THROWS(*vec3Old = 10.0);
 //   vec1Old = &vec1[0];
  }
  // Test destructor memory leak
//  REQUIRE_THROWS(*vec1Old = 10.0);
 
  DoubleVector vec4(5);
  vec4.Fill(3.0);

  vec2.Fill(1.0);
  DoubleVector vec3(5);
  vec3.Fill(2.0);
  vec3 = (vec2 = vec4);
  vec4.Fill(5.0);
  // Test double assignment 1
  REQUIRE((vec2.GetLength() == 5 &&
           vec2[0] == 3.0 && vec2[1] == 3.0 && vec2[2] == 3.0 &&
           vec2[3] == 3.0 && vec2[4] == 3.0));
  vec2.Fill(7.0);
  // Test double assignment 2
  REQUIRE((vec3.GetLength() == 5 &&
           vec3[0] == 3.0 && vec3[1] == 3.0 && vec3[2] == 3.0 &&
           vec3[3] == 3.0 && vec3[4] == 3.0));
  // Test self assignment
  REQUIRE_NOTHROW(vec3 = vec3);
  REQUIRE((vec3.GetLength() == 5 &&
           vec3[0] == 3.0 && vec3[1] == 3.0 && vec3[2] == 3.0 &&
           vec3[3] == 3.0 && vec3[4] == 3.0)); 
}

TEST_CASE("Test2", "[PlusMinus]") {
  DoubleVector vec1(5);
  DoubleVector vec2(5);
  vec1.Fill(2.0);
  vec2.Fill(4.0);

  DoubleVector vec3 = vec1 + vec2;
  REQUIRE((vec3.GetLength() == 5 &&
           vec3[0] == 6.0 && vec3[1] == 6.0 && vec3[2] == 6.0 &&
           vec3[3] == 6.0 && vec3[4] == 6.0)); 
  vec3 = vec2 - vec1;
  REQUIRE((vec3.GetLength() == 5 &&
           vec3[0] == 2.0 && vec3[1] == 2.0 && vec3[2] == 2.0 &&
           vec3[3] == 2.0 && vec3[4] == 2.0)); 
}

TEST_CASE("Test3", "[ScalarMult]") {
  DoubleVector vec1(5);
  vec1.Fill(4.0);
  DoubleVector vec3 = 2.0 * vec1;
  REQUIRE((vec3.GetLength() == 5 &&
           vec3[0] == 8.0 && vec3[1] == 8.0 && vec3[2] == 8.0 &&
           vec3[3] == 8.0 && vec3[4] == 8.0));
  vec3 = vec1 * 2.0;
  REQUIRE((vec3.GetLength() == 5 &&
           vec3[0] == 8.0 && vec3[1] == 8.0 && vec3[2] == 8.0 &&
           vec3[3] == 8.0 && vec3[4] == 8.0)); 
  
}

TEST_CASE("Test4", "[Stream]") {
  std::ostringstream oss;
  DoubleVector vec1(5);
  DoubleVector vec2(5);
  vec1.Fill(3.0);
  vec2.Fill(4.0);

  oss << vec1 << vec2 << vec1 + vec2;
  std::string s = oss.str();
  std::string expected = "(3, 3, 3, 3, 3)(4, 4, 4, 4, 4)(7, 7, 7, 7, 7)";
  REQUIRE((s == expected));
}
