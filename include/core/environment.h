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
  Environment(size_t length, size_t height);

  /**
   * Constructor to initialize environment with length and height
   * @param length Length of the (rectangular) environment
   * @param height height of the environment
   * @param organisms A vector of starting organisms
   */
  Environment(size_t length, size_t height, std::vector<Organism>& organisms);

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
  Environment(size_t length, size_t height, double total_calories,
              size_t num_food, size_t num_starting_organisms);

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
  Environment(size_t length, size_t height, double total_calories,
              size_t num_food, size_t num_starting_organisms,
              size_t length_of_day);

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
  Environment(size_t length, size_t height, double total_calories,
              size_t num_food, size_t num_starting_organisms,
              size_t length_of_day, double starting_speed,
              double starting_size);

  /**
   * Constructor to initialize environment from a text file
   * @param file_path The path to the text file
   */
  Environment(std::string file_path);

  /**
   * Function to reset the environment after the end of each day
   */
  void Reset();

  /**
   * Function to update the state of the environment. Called every frame.
   */
  void Update();

  /**
   * Function to reset all organisms at the end of each day of the simulation
   */
  void ResetOrganisms();

  /**
   * Function to remove organisms that have not survived at the end of each day
   */
  void RemoveDeadOrganisms();

  /**
   * Function to add new organisms to the environment at the end of each day
   */
  void AddNewOrganisms();

  /**
   * Function to fill the Food vector of the environment
   */
  void AddFood();

  /**
   * Getter method for length
   * @return length_
   */
  size_t length() const {
    return length_;
  }

  /**
   * Getter method for height
   * @return height_
   */
  size_t height() const {
    return height_;
  }

  /**
   * Function to check if the simulation is at the end of a day
   * @return True if the simulation is at the end of a day, else false
   */
  bool IsEndOfDay() const {
    return (time_elapsed_ >= length_of_day_);
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

  /**
   * Getter method for the number of days elapsed
   * @return days_
   */
  const size_t days() const {
    return days_;
  }

  /**
   * Getter method for the population data
   * @return population_
   */
  const std::vector<int>& population() const {
    return population_;
  }

  /**
   * Getter method for the sizes vector
   * @return sizes_
   */
  const std::vector<double>& sizes() const {
    return sizes_;
  }

  /**
   * Getter method for the speeds vector
   * @return speeds_
   */
  const std::vector<double>& speeds() const {
    return speeds_;
  }

 private:
  size_t length_;
  size_t height_;
  size_t length_of_day_;

  size_t num_food_;
  // The total number of calories of all the food in the environment
  double total_calories_;
  // Vector of food objects that spawn everyday
  std::vector<Food> food_;
  // Vector of surviving organisms that exist in the environment
  std::vector<Organism> organisms_;
  // The number of frames that have elapsed since the day began. Gets reset to
  // zero at the end of each day
  size_t time_elapsed_;
  // The number of days passed
  size_t days_ = 1;
  // A vector storing the population of the environment as a function of days
  std::vector<int> population_;
  // A vector storing the speeds of all organisms
  std::vector<double> speeds_;
  // A vector storing the sizes of all organisms
  std::vector<double> sizes_;

  // Helper Methods:
  /**
   * Function to add initial organisms to the environment
   * @param num_organisms The number of organisms to be added
   * @param size The size of the organisms
   * @param speed The speed of the organisms
   */
  void AddOrganisms(size_t num_organisms, double speed, double size);

  /**
   * Function to randomly kill some organisms at the end of each day, with the
   * probability varying with the size of the organism
   */
   void RemoveRandomOrganisms();
};
} // namespace naturalselection