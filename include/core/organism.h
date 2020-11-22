#pragma once

#include <cinder/gl/gl.h>
#include "gene.h"
#include "food.h"

namespace naturalselection {

/**
 * Class which represents an organism
 */
class Organism {
 public:
  /**
   * Constructor to initialize an organism object
   * @param speed- the genetic trait for speed of the organism
   * @param size- the genetic trait for size of the organism
   */
  Organism(double speed, double size);

  /**
   * Function called when an organism eats food
   * @param food- The Food object that the organism has eaten
   */
  void Eat(const Food& food);

  /**
   * Function called to update the velocity and position of the organism
   * throughout the simulation. The organism will randomly move through the
   * environment.
   */
  void Move();

  /**
   * Function to reset the organism after each day of the simulation. This
   * includes resetting the organism's position, velocity, and calories gained
   * @param pos- The new position of the organism
   * @param vel- The new velocity of the organism
   */
  void ResetForDay(glm::vec2 pos, glm::vec2 vel);

  /**
   * Function to check if the organism will survive for the day based on its
   * current calories gained
   * @return true if the organism will survive, else return false
   */
  bool WillSurvive() const;

  /**
  * Function to check if the organism will replicate based on its current
  * calories gained
  * @return true if the organism will replicate, else return false
  */
  bool WillReplicate() const;

  /**
   * Function called when an organism replicates
   * @return A new organism, with genetic traits depending on this organism's
   * traits and the transfer coefficients of the genes.
   */
  Organism Replicate() const;

  /**
   * Function to expend the energy of the organism
   * @return the energy expended
   */
  double ExpendEnergy();

  /**
   * Function to update the state of the organism during the simulation
   */
  void Update();

  /**
   * Function to set the gene for speed of all the organisms
   * @param transfer_coefficient- The transfer coefficient of the gene
   * @param max_percent_change- The maximum change in a trait value from one
   * generation to the next
   */
  static void SetSpeedGene(double transfer_coefficient,
                           double max_percent_change);

  /**
   * Function to set the gene for speed of all the organisms
   * @param transfer_coefficient- The transfer coefficient of the gene
   * @param max_percent_change- The maximum change in a trait value from one
   * generation to the next
   */
  static void SetSizeGene(double transfer_coefficient,
                          double max_percent_change);

  /**
   * Function to set the survivability threshold (the minimum amount of
   * calories from food that the organism must consume to survive for a day)
   * @param survivability_threshold- The survivability threshold for all
   * organisms
   */
  static void SetSurvivabilityThreshold(double survivability_threshold);

  /**
   * Function to set the replication threshold (the minimum amount of calories
   * from food that the organism must consume to replicate).
   * @param replication_threshold- The replication threshold for all
   * organisms
   */
  static void SetReplicationThreshold(double replication_threshold);

  /**
   * Function to set the maximum energy that an organism can expend in one day
   * @param max_energy- The maximum energy an organism can expend
   */
  static void SetMaximumEnergy(double max_energy);

  /**
   * Getter method for speed
   * @return speed_
   */
  double speed() {
    return speed_;
  }

  /**
   * Getter method for size
   * @return size_
   */
  double size() {
    return size_;
  }
 private:
  // Genetic traits which are constant for a given organism
  const double speed_;
  const double size_;

  // Variables which change throughout the simulation
  double calories_gained_;
  double current_energy_expended_;
  glm::vec2 position_;
  glm::vec2 velocity_;

  // These genes are the same for all organisms
  static Gene speed_gene_;
  static Gene size_gene_;

  // These values are same for all organisms
  static double max_energy_;
  static double survivability_threshold_;
  static double replication_threshold_;
};


} // namespace naturalselection
