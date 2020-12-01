#include "core/environment.h"
#include <catch2/catch.hpp>

using namespace naturalselection;

TEST_CASE("AddFood and ResetOrganisms") {
  Environment environment(600, 600);
  for (const Organism& organism : environment.organisms()) {
    REQUIRE((organism.position().x == organism.size() ||
             organism.position().x == environment.length() - organism.size() ||
             organism.position().y == organism.size() ||
             organism.position().y == environment.height() - organism.size()));
  }
  for (const Food& food : environment.food()) {
    REQUIRE(((food.position_.x <= 3 * environment.length() / 4) &&
            (food.position_.x >= environment.length() / 4)));
    REQUIRE(((food.position_.y <= 3 * environment.height() / 4) &&
             (food.position_.x >= environment.height() / 4)));
  }
}
