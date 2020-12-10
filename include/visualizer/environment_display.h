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

  /**
   * Function to draw the environment and all organisms within it
   */
  void Draw();

  /**
   * Function to update the state of the environment
   */
  void Update();

  /**
   * Getter method for the environment
   * @return environment_
   */
  const Environment& environment() const {
    return environment_;
  }

  /**
   * Getter method for the population data of environment_
   * @return population_ of environment
   */
  const std::vector<int>& population() const {
    return environment_.population();
  }

  /**
   * Getter function for the number of organisms in the environment
   * @return size of the organisms vector
   */
  size_t num_organisms() const {
    return environment_.organisms().size();
  }

  /**
   * Function to obtain the speeds vector of the environment
   * @return environment_.speeds()
   */
  const std::vector<double>& speeds() const {
    return environment_.speeds();
  }

  /**
   * Function to obtain the sizes vector of the environment
   * @return environment_.sizes()
   */
  const std::vector<double>& sizes() const {
    return environment_.sizes();
  }

 private:
  Environment environment_;
  glm::vec2 top_left_corner_;

  const ci::Font font = ci::Font("Arial", 18);

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