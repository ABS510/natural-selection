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
   * Constructor to initialize environment with length and height
   * @param length Length of the (rectangular) environment
   * @param height height of the environment
   */
  Environment(int length, int height);

  /**
   * Constructor to initialize environment with length and height, as well
   * as the total number of calories of the environment and the number of
   * organisms to start with.
   * @param length Length of the (rectangular) environment
   * @param height height of the environment
   * @param num_starting_organisms The number of organisms at the start of the
   * simulation
   * @param total_calories The number of calories (in food) in the environment
   * @param num_food The number of food objects in the environment
   */
  Environment(int length, int height, double total_calories, int num_food,
              int num_starting_organisms);

  /**
   * Constructor to initialize environment with length and height, as well
   * as the total number of calories of the environment and the number of
   * organisms to start with.
   * @param length Length of the (rectangular) environment
   * @param height height of the environment
   * @param num_starting_organisms The number of organisms at the start of the
   * simulation
   * @param total_calories The number of calories (in food) in the environment
   * @param num_food The number of food objects in the environment
   * @param length_of_day The number of frames for which each day will last for
   */
  Environment(int length, int height, double total_calories, int num_food,
              int num_starting_organisms, int length_of_day);

  /**
  * Constructor to initialize environment with length and height, as well
  * as the total number of calories of the environment and the number of
  * organisms to start with.
  * @param length Length of the (rectangular) environment
  * @param height height of the environment
  * @param num_starting_organisms The number of organisms at the start of the
      * simulation
  * @param total_calories The number of calories (in food) in the environment
  * @param num_food The number of food objects in the environment
  * @param length_of_day The number of frames for which each day will last for
  * @param starting_speed The speed of the first generation of organisms
  * @param starting_size The size of the first generation of organisms
  */
  Environment(int length, int height, double total_calories, int num_food,
              int num_starting_organisms, int length_of_day,
              double starting_speed, double starting_size);

  /**
   * Function to reset the environment after the end of each day
   */
  void Reset();

  /**
   * Function to update the state of the environment. Called every frame.
   */
  void Update();

  /**
   * Getter method for length
   * @return length_
   */
  int length() {
    return length_;
  }

  /**
   * Getter method for height
   * @return height_
   */
  int height() {
    return height_;
  }

  /**
   * Getter method for list of Organisms
   * @return organisms_
   */
  const std::vector<Organism>& organisms() const {
    return organisms_;
  }

  /**
   * Getter method for list of food objects
   * @return food_
   */
  const std::vector<Food>& food() const {
    return food_;
  }

 private:
  const int length_;
  const int height_;
  const int length_of_day_;

  int num_food_;
  double total_calories_;

  // Vector of food objects that spawn everyday
  std::vector<Food> food_;
  // Vector of surviving organisms that exist in the environment
  std::vector<Organism> organisms_;
  // The number of frames that have elapsed since the day began. Gets reset to
  // zero at the end of each day
  int time_elapsed_;
  // Helper Methods:

  /**
   * Function to remove organisms that have not survived at the end of each day
   */
  void RemoveDeadOrganisms();

  /**
   * Function to add new organisms to the environment at the end of each day
   */
  void AddNewOrganisms();

  /**
   * Helper function to fill the Food vector of the environment
   */
  void AddFood();

  /**
   * Function to add initial organisms to the environment
   * @param num_organisms The number of organisms to be added
   * @param size The size of the organisms
   * @param speed The speed of the organisms
   */
  void AddOrganisms(int num_organisms, double speed, double size);

  /**
   * Function to reset all organisms at the end of each day of the simulation
   */
  void ResetOrganisms();
};
} // namespace naturalselection