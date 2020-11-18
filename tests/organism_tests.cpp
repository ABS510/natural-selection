#include "core/organism.h"
#include <catch2/catch.hpp>

using namespace naturalselection;

TEST_CASE("Will Survive") {
  Organism::SetSurvivabilityThreshold(100);
  Organism organism(10, 10);
  organism.ResetForDay(glm::vec2(0,0), glm::vec2(0,10));

  organism.Eat(Food(glm::vec2(10,10), "red", 50));
  REQUIRE_FALSE(organism.WillSurvive());
  organism.Eat(Food(glm::vec2(10,10), "red", 50));
  REQUIRE(organism.WillSurvive());
}

TEST_CASE("Will Replicate") {
  Organism::SetSurvivabilityThreshold(200);
  Organism organism(10, 10);
  organism.ResetForDay(glm::vec2(0,0), glm::vec2(0,10));

  organism.Eat(Food(glm::vec2(10,10), "red", 150));
  REQUIRE_FALSE(organism.WillReplicate());
  organism.Eat(Food(glm::vec2(10,10), "red", 50));
  REQUIRE(organism.WillReplicate());
}

TEST_CASE("Replicate") {
  Organism::SetSizeGene(100, 0.15);
  Organism::SetSpeedGene(100, 0.1);
  Organism parent(100, 100);

  for(size_t i = 0; i < 100; i++) {
    Organism child = parent.Replicate();
    REQUIRE(90 <= child.speed());
    REQUIRE (child.speed() <= 110);
    REQUIRE(85 <= child.size());
    REQUIRE(child.size() <= 115);
  }
}