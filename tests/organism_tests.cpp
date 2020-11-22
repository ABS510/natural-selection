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
  Organism parent1(100, 100);
  Organism parent2(50,200);

  for(size_t i = 0; i < 100; i++) {
    Organism child1 = parent1.Replicate();
    REQUIRE((90 <= child1.speed() && child1.speed() <= 110));
    REQUIRE(((85 <= child1.speed()) && (child1.speed() <= 115)));

    Organism child2 = parent2.Replicate();
    REQUIRE(((45 <= child2.speed()) && (child2.speed() <= 55)));
    REQUIRE(((170 <= child2.size()) && (child2.size() <= 230)));
  }
}