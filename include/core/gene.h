#pragma once

namespace naturalselection {

/**
 * Class to represent the gene characteristics of a species.
 * Probability distribution used is from a bell curve
 */
class Gene {
 public:
  /**
   * Constructor to create a gene object
   * @param transfer_coefficient- A number corresponding to how much and how
   * likely a genetic trait will change
   */
  Gene(double transfer_coefficient);

  /**
   * Constructor to create a gene object
   * @param transfer_coefficient- A number corresponding to how much and how
   * likely a genetic trait will change
   * @param max_percent_change- The maximum percentage by which a genetic trait
   * can change over a single evolution
   */
  Gene(double transfer_coefficient, double max_percent_change);

  /**
   * Function to calculate the change in a trait from the parent to offspring
   * @param trait_value The value of the original trait of the parent
   * @param random_num A random double from -1 to 1, which will decide how
   * much a trait is changed (the change is capped by max_percent_change_)
   * @return The change in value of the trait from the parent to offspring
   */
  double CalculateTraitChange(double trait_value, double random_num);

  /**
   * Function to generate the value of a trait of an offspring
   * @param trait_value The value of the original trait of the parent
   * @return The value of the trait of the offspring
   */
  double GenerateEvolvedTrait(double trait_value);

 private:
  /**
   * Coefficient for determining how much a trait will change from parent to
   * offspring. Higher the value of this coefficient, lower is the change of
   * a genetic trait.
   */
  double transfer_coefficient_;

  /**
   * The maximum that a genetic trait can change relative to the original trait
   * of the parent. Must be greater than 0.
   */
  double max_percent_change_;
};
} //  namespace naturalselection