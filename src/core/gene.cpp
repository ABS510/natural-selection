#include "core/gene.h"
#include <stdexcept>

namespace naturalselection {

Gene::Gene(double transfer_coefficient) {
  transfer_coefficient_ = transfer_coefficient;
  max_percent_change_ = 0.15;
}

Gene::Gene(double transfer_coefficient, double max_percent_change) {
  transfer_coefficient_ = transfer_coefficient;
  if (max_percent_change < 0) {
    throw std::out_of_range("max_percentage change must be above 0!");
  }
  max_percent_change_ = max_percent_change;
}

double Gene::CalculateTraitChange(double trait_value, double random_num) {
  if (abs(random_num) > 1) {
    throw std::invalid_argument("Random number is greater than 1");
  }

  double trait_change_multiplier = max_percent_change_;
  if (random_num != 0) {
    double change_squared = -log(abs(random_num)) / transfer_coefficient_;
    trait_change_multiplier = sqrt(change_squared);
  }

  if (trait_change_multiplier > max_percent_change_) {
    trait_change_multiplier = max_percent_change_;
  }
  if (random_num < 0) {
    trait_change_multiplier = -trait_change_multiplier;
  }
  double trait_change = trait_change_multiplier * trait_value;
  return trait_change;
}

double Gene::GenerateEvolvedTrait(double trait_value) {
  // Generate random double between -1 and 1
  double random_number = (2 * ((double) rand() / (double) RAND_MAX)) - 1;
  double trait_change = CalculateTraitChange(trait_value, random_number);
  double evolved_trait_value = trait_change + trait_value;
  return evolved_trait_value;
}
} // namespace naturalselection