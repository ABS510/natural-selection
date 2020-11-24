#include "visualizer/environment_display.h"

namespace naturalselection {
EnvironmentDisplay::EnvironmentDisplay(Environment environment,
                                       glm::vec2 top_left_corner)
    : environment_(environment) {
  top_left_corner_ = top_left_corner;
}

void EnvironmentDisplay::Draw() {
  for (const Organism& organism : environment_.organisms()) {
    DrawOrganism(organism);
  }
  for (const Food& food : environment_.food()) {
    DrawFood(food);
  }
}

void EnvironmentDisplay::DrawFood(const Food &food) {
  ci::gl::color(food.color_);
  ci::gl::drawSolidCircle(food.position_ + top_left_corner_, 4);
}

void EnvironmentDisplay::DrawOrganism(const Organism& organism) {
  ci::gl::color(255, 255 - 5 * organism.speed(), 255 - 5 * organism.speed());
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
}