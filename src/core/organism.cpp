#include "core/organism.h"

namespace naturalselection {

Gene Organism::speed_gene_(50, 0.1);
Gene Organism::size_gene_(50, 0.1);
double Organism::max_energy_(50);
double Organism::survivability_threshold_(100);
double Organism::replication_threshold_(180);

Organism::Organism(double speed, double size)
    : speed_(speed), size_(size) {
  // Set to default values
  calories_gained_ = 0;
  current_energy_expended_ = 0;
  position_ = glm::vec2(0,0);
  velocity_ = glm::vec2(0,speed_);
}

bool Organism::Eat(const Food& food) {
  if (!WillReplicate()) {
    if (glm::length(food.position_ - position_) <= size_) {
      calories_gained_ += food.calories_;
      return true;
    }
  }
  return false;
}

void Organism::Move(int length, int height, const std::vector<Food>& food) {
  if (!WillReplicate()) {
    glm::vec2 target(length / 2, height / 2);
    double min_dist = length * length + height * height;
    for (const Food& food_ : food) {
      if (glm::length(food_.position_ - position_) < min_dist &&
          glm::length(food_.position_ - position_) < 5 * size_) {
        target = food_.position_;
        min_dist = glm::length(food_.position_ - position_);
      }
    }
    velocity_ =
        (float)speed_ * (target - position_) / glm::length(target - position_);
    if (food.size() == 0) {
      velocity_ = glm::vec2(0, 0);
    }
    position_ += velocity_;
  }
}

bool Organism::WillSurvive() const {
  return (calories_gained_ >= survivability_threshold_);
}

bool Organism::WillReplicate() const {
  return (calories_gained_ >= replication_threshold_);
}

Organism Organism::Replicate() const {
  double new_speed = speed_gene_.GenerateEvolvedTrait(speed_);
  double new_size = size_gene_.GenerateEvolvedTrait(size_);
  return Organism(new_speed, new_size);
}

void Organism::ResetForDay(glm::vec2 pos) {
  position_ = pos;
  calories_gained_ = 0;
  current_energy_expended_ = 0;
}

double Organism::ExpendEnergy() {
  double energy_expended = speed_ * speed_ + 0.01 * size_ * size_ * size_;
  current_energy_expended_ += energy_expended;
  return energy_expended;
}

void Organism::Update(int length, int height, const std::vector<Food>& food) {
  if (current_energy_expended_ < max_energy_) {
    Move(length, height, food);
    ExpendEnergy();
  }
}

void Organism::SetSpeedGene(double transfer_coefficient,
                           double max_percent_change) {
  speed_gene_ = Gene(transfer_coefficient, max_percent_change);
}

void Organism::SetSizeGene(double transfer_coefficient,
                           double max_percent_change) {
  size_gene_ = Gene(transfer_coefficient, max_percent_change);
}

void Organism::SetReplicationThreshold(double replication_threshold) {
  replication_threshold_ = replication_threshold;
}

void Organism::SetSurvivabilityThreshold(double survivability_threshold) {
  survivability_threshold_ = survivability_threshold;
}

void Organism::SetMaximumEnergy(double max_energy) {
  max_energy_ = max_energy;
}
} // namespace naturalselection