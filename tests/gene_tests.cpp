#include "core/gene.h"
#include <catch2/catch.hpp>

using namespace naturalselection;

TEST_CASE("Calculate Trait Changes") {
  Gene gene(30, 0.2);

  SECTION("Random number is 0") {
    double change = gene.CalculateTraitChange(100, 0);
    REQUIRE(change == Approx(20));
  }

  SECTION("Random number is 1") {
    double change = gene.CalculateTraitChange(100, 1);
    REQUIRE(change == Approx(0));
  }

  SECTION("Random number is -1") {
    double change = gene.CalculateTraitChange(100, -1);
    REQUIRE(change == Approx(0));
  }

  SECTION("Random number is positive") {
    double change = gene.CalculateTraitChange(100, 0.5);
    REQUIRE(change == Approx(15.200298));
  }

  SECTION("Random number is negative") {
    double change = gene.CalculateTraitChange(100, -0.5);
    REQUIRE(change == Approx(-15.200298));
  }

  SECTION("Trait change is greater than max percent change") {
    double change = gene.CalculateTraitChange(43, -0.1);
    REQUIRE(change == Approx(-8.6));
  }

  SECTION("Random number is out of range") {
    REQUIRE_THROWS_AS(gene.CalculateTraitChange(1, 5), std::invalid_argument);
    REQUIRE_THROWS_AS(gene.CalculateTraitChange(1, -9), std::invalid_argument);
  }
}

TEST_CASE("Test Generate Evolved Trait") {
  Gene gene(30, 0.2);
  double avg = 0;
  for (int i = 0; i < 100; i++) {
    avg += abs(gene.GenerateEvolvedTrait(100) - 100);
  }
  avg = avg / 100;
  REQUIRE((avg < 20) & (avg > 10));
}