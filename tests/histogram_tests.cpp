#include "visualizer/histogram.h"
#include <catch2/catch.hpp>

using namespace naturalselection;

TEST_CASE("Get Bin") {
  Histogram histogram(glm::vec2(0,0), 100, 100, "", "", 10, 30, 10);
  SECTION("Value between 0 and max_x") {
    REQUIRE(histogram.GetBin(1.5) == 1);
  }

  SECTION("Value less than 0") {
    REQUIRE(histogram.GetBin(-20) == 0);
  }

  SECTION("Value greater than max_x") {
    REQUIRE(histogram.GetBin(20) == 9);
  }
}

