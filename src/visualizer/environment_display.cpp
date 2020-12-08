#include "visualizer/environment_display.h"

namespace naturalselection {
EnvironmentDisplay::EnvironmentDisplay(Environment environment,
                                       glm::vec2 top_left_corner)
    : environment_(environment) {
  top_left_corner_ = top_left_corner;
}

void EnvironmentDisplay::Draw() {
  ci::gl::color(1, 1, 1);
  // Display current population and number of days elapsed
  ci::gl::drawString(
      "Population:" + std::to_string(environment_.organisms().size()) +
          "\t Day:" + std::to_string(environment_.days()),
      top_left_corner_ - glm::vec2(0,18), ci::Color8u("white"),
      ci::Font("Arial",18));

  DrawEnvironment();

  for (const Organism& organism : environment_.organisms()) {
    DrawOrganism(organism);
  }
  for (const Food& food : environment_.food()) {
    DrawFood(food);
  }
}

void EnvironmentDisplay::Update() {
  environment_.Update();
}

void EnvironmentDisplay::DrawFood(const Food &food) {
  ci::gl::color(food.color_);
  const int food_size = 4;
  ci::Rectf food_square(
      top_left_corner_ + food.position_ - glm::vec2(food_size,food_size),
      top_left_corner_ + food.position_ + glm::vec2(food_size,food_size));
  ci::gl::drawSolidRect(food_square);
}

void EnvironmentDisplay::DrawOrganism(const Organism& organism) {
  // Display the organism as more red depending on its speed
  float red_shade = ((255.0 - (25 * organism.speed()))) / 255;
  if (red_shade <= 0) {
    red_shade = 0;
  }
  ci::gl::color(1, red_shade, red_shade);
  ci::gl::drawSolidCircle(
      organism.position() + top_left_corner_, organism.size());
}

void EnvironmentDisplay::DrawEnvironment() {
  glm::vec2 bottom_right_corner = top_left_corner_ +
                    glm::vec2(environment_.length(), environment_.height());
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);

  ci::gl::color(0, 0, 0);
  ci::gl::drawSolidRect(pixel_bounding_box);
  ci::gl::color(255, 255, 255);
  ci::gl::drawStrokedRect(pixel_bounding_box);
}
} // namespace naturalselection