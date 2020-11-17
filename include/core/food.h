#pragma once
#include <cinder/gl/gl.h>

namespace naturalselection {

/**
 * Struct representing food that an organism can consume
 */
struct Food {
  /**
   * Constructor for the food object
   * @param position- The position of the food
   * @param color- the color of the food
   * @param calories- the calories/energy contained by the food
   */
  Food(glm::vec2 position, ci::Color8u color, double calories) {
    position_ = position;
    color_ = color;
    calories_ = calories;
  }

  // The location of the food object in the environment
  glm::vec2 position_;
  // The color of the food (used for drawing)
  ci::Color8u color_;
  // The energy this food object provides for the organism that consumes it
  double calories_;
};
} //  namespace naturalselection