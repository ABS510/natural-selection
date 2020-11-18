#pragma once

#include <cinder/gl/gl.h>
#include "core/food.h"
#include "core/organism.h"

namespace naturalselection {

/**
 * Class representing the environment
 */
class Environment {
 public:
  /**
   * Default constructor
   */
  Environment();

  /**
   * Constructor to initialize envoronment with length and height
   * @param length Length of the (rectangular) environment
   * @param height height of the environment
   */
  Environment(double length, double height);

  /**
   * Function to reset the environment after the end of each day
   */
  void Reset();

  /**
   * Function to update the state of the environment. Called every frame.
   */
  void Update();
 private:
  const double length_;
  const double height_;
  const int length_of_day_;
  // Vector of food objects that spawn everyday
  std::vector<Food> food_;
  // Vector of surviving organisms that exist in the environment
  std::vector<Organism> organisms_;

  // Helper Methods:

  /**
   * Function to remove organisms that have not survived atthe end of each day
   */
  void RemoveDeadOrganisms();

  /**
   * Function to add new organisms to the environment at the end of each day
   */
  void AddNewOrganisms();

};
} // namespace naturalselection