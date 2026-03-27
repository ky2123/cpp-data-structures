#include "catch.hpp"
#include "intarray.h"

TEST_CASE("set and retrieve element 0") {
  cside::IntArray arr(10);
  arr.set(0,3);

 REQUIRE(arr.get(0) == 3);
}

TEST_CASE("get() returns consistent addresses") {
  cside::IntArray arr(5);

  REQUIRE(&arr.get(1) == &arr.get(1));
}
TEST_CASE("copy ctor creates new block") {
  // arrange
  cside::IntArray src(5);
  src.set(0,10);
  // act
  cside::IntArray copy(src);
  copy.set(0,3);

  //assert
  REQUIRE(src.get(0) == 10);
  REQUIRE(copy.get(0) == 3);
  REQUIRE(&src.get(0) != & copy.get(0));
}
