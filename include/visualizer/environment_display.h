#pragma once

#include <cinder/gl/gl.h>
#include "core/environment.h"

namespace naturalselection {

/**
 * Class for displaying the environment and everything contained within it
 */
class EnvironmentDisplay {
 public:
  /**
   * Constructor to initialize the EnvironmentDisplay object
   * @param environment The environment object to be displayed
   * @param top_left_corner The top left corner of the environment
   */
  EnvironmentDisplay(Environment environment, glm::vec2 top_left_corner);

  void Draw();

  void Update();

 private:
  Environment environment_;
  glm::vec2 top_left_corner_;

  /**
   * Function to draw a Food object
   * @param food The food object to be drawn
   */
  void DrawFood(const Food& food);

  /**
   * Function to draw an Organism
   * @param organism The organism to be drawn
   */
  void DrawOrganism(const Organism& organism);

  /**
   * Function to draw the environment
   */
  void DrawEnvironment();
};
}