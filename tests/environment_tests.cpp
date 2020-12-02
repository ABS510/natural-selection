#include "core/environment.h"
#include <catch2/catch.hpp>

using namespace naturalselection;

TEST_CASE("Add Food") {
  Environment environment(600, 600);
  environment.AddFood();
  for (const Food& food : environment.food()) {
    REQUIRE(((food.position_.x <= 3 * environment.length() / 4) &&
             (food.position_.x >= environment.length() / 4)));
    REQUIRE(((food.position_.y <= 3 * environment.height() / 4) &&
             (food.position_.x >= environment.height() / 4)));
  }
}

TEST_CASE("Reset Organisms") {
  Environment environment(600, 600);
  environment.ResetOrganisms();
  for (const Organism& organism : environment.organisms()) {
    REQUIRE((organism.position().x == organism.size() ||
             organism.position().x == environment.length() - organism.size() ||
             organism.position().y == organism.size() ||
             organism.position().y == environment.height() - organism.size()));
  }
}

TEST_CASE("Remove Dead Organisms") {
  std::vector<Organism> organisms(5, Organism(5, 10));
  Organism::SetSurvivabilityThreshold(200);
  Organism::SetReplicationThreshold(300);
  for (Organism& organism : organisms) {
    organism.ResetForDay(glm::vec2(0,0));
  }
  // These 2 organisms will survive
  organisms[2].Eat(Food(glm::vec2(0,0), 300));
  organisms[4].Eat(Food(glm::vec2(0,0), 300));

  Environment environment(600, 600, organisms);
  environment.RemoveDeadOrganisms();
  REQUIRE(environment.organisms().size() == 2);
}