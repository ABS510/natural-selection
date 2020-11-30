#include "core/organism.h"
#include <catch2/catch.hpp>

using namespace naturalselection;

TEST_CASE("Reset for day") {
  Organism::SetSurvivabilityThreshold(100);
  Organism organism(10, 10);
  organism.Eat(Food(glm::vec2(10,10), "red", 50));
  organism.ResetForDay(glm::vec2(4,7));
  REQUIRE(organism.position() == glm::vec2(4,7));
  REQUIRE(organism.WillSurvive() == false);
  REQUIRE(organism.WillReplicate() == false);
}

TEST_CASE("Will Survive") {
  Organism::SetSurvivabilityThreshold(100);
  Organism organism(10, 10);
  organism.ResetForDay(glm::vec2(10,10));

  organism.Eat(Food(glm::vec2(10,10), "red", 50));
  REQUIRE_FALSE(organism.WillSurvive());
  organism.Eat(Food(glm::vec2(10,10), "red", 50));
  REQUIRE(organism.WillSurvive());
}

TEST_CASE("Will Replicate") {
  Organism::SetSurvivabilityThreshold(200);
  Organism organism(10, 10);
  organism.ResetForDay(glm::vec2(10,10));

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

TEST_CASE("Expend Energy") {
  SECTION("0 speed") {
    Organism organism (0, 10);
    REQUIRE(organism.ExpendEnergy() == 1);
  }

  SECTION("0 size") {
    Organism organism (10, 0);
    REQUIRE(organism.ExpendEnergy() == 100);
  }

  SECTION("Random size and speed") {
    Organism organism (7, 12);
    REQUIRE(organism.ExpendEnergy() == 50.728);
  }
}

TEST_CASE("Move") {
  SECTION("Environment has no food") {
    Organism organism (7, 12);
    organism.ResetForDay(glm::vec2(0, 0));
    organism.Move(100, 100, std::vector<Food>());
    REQUIRE(organism.position() == glm::vec2(0, 0));
  }

  SECTION("Environment has 1 food object but is out of vision of organism") {
    Organism organism (10, 2);
    organism.ResetForDay(glm::vec2(50, 0));
    std::vector<Food> food_vector(1, Food(glm::vec2(90, 90), 50));
    organism.Move(100, 100, food_vector);
    REQUIRE(organism.position() == glm::vec2(50, 10));
  }

  SECTION("Environment has 1 food object in vision of organism") {
    Organism organism (10, 20);
    organism.ResetForDay(glm::vec2(90, 0));
    std::vector<Food> food_vector(1, Food(glm::vec2(90, 90), 50));
    organism.Move(100, 100, food_vector);
    REQUIRE(organism.position() == glm::vec2(90, 10));
  }

  SECTION("Environment has multiple food objects in vision of organism") {
    Organism organism (10, 20);
    organism.ResetForDay(glm::vec2(40, 0));
    std::vector<Food> food_vector(1, Food(glm::vec2(90, 90), 50));
    food_vector.push_back(Food(glm::vec2(40, 20), 50));
    organism.Move(100, 100, food_vector);
    REQUIRE(organism.position() == glm::vec2(40, 10));
  }
}