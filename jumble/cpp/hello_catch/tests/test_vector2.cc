
#include <catch/catch.hpp>

#include "src/vector.h"

TEST_CASE("Constructors", "Vector2") {
  Vector2 v1 = Vector2();
  REQUIRE(v1.x == 0);
  REQUIRE(v1.y == 0);

  Vector2 v2 = Vector2(1.1, 2);
  REQUIRE(v2.x == 1.1);
  REQUIRE(v2.y == 2.0);

  Vector2 v3 = Vector2(v2);
  REQUIRE(v3.x == 1.1);
  REQUIRE(v3.y == 2.0);

  v3.y = 8;
  REQUIRE(v3.x == 1.1);
  REQUIRE(v3.y == 8);

  v3.x = 6.9;
  REQUIRE(v3.x == 6.9);
  REQUIRE(v3.y == 8);
}

TEST_CASE("GetNorm", "Vector2") {
  const double epsilon = 0.0001;
  Vector2 v1 = Vector2();
  REQUIRE(v1.GetNorm() == 0);

  Vector2 v2 = Vector2(3, 4);
  REQUIRE(v1.GetNorm() - 5 <= epsilon);
}
