#include "core/environment.h"
#include <fstream>
#include <iostream>

namespace naturalselection {

Environment::Environment(size_t length, size_t height)
    : Environment(length, height, 1000, 30,
                  20, 240) {}

Environment::Environment(size_t length, size_t height,
                         std::vector<Organism>& organisms)
    : length_(length) , height_(height), length_of_day_(240) {
  total_calories_ = 1000;
  num_food_ = 30;
  AddFood();
  organisms_ = organisms;
  for (Organism organism : organisms) {
    speeds_.push_back(organism.speed());
    sizes_.push_back(organism.size());
  }
  time_elapsed_ = 0;
}

Environment::Environment(size_t length, size_t height, double total_calories,
                         size_t num_food, size_t num_starting_organisms)
    : Environment(length, height, total_calories, num_food,
                  num_starting_organisms, 240) {}

Environment::Environment(size_t length, size_t height, double total_calories,
                         size_t num_food, size_t num_starting_organisms,
                         size_t length_of_day)
    : Environment(length, height, total_calories, num_food,
                  num_starting_organisms, 240, 4, 10) {}

Environment::Environment(size_t length, size_t height, double total_calories,
                         size_t num_food, size_t num_starting_organisms,
                         size_t length_of_day, double starting_speed,
                         double starting_size)
    : length_(length) , height_(height), length_of_day_(length_of_day) {
  total_calories_ = total_calories;
  num_food_ = num_food;
  AddFood();
  AddOrganisms(num_starting_organisms, starting_speed, starting_size);
  ResetOrganisms();
  population_.push_back(num_starting_organisms);
  time_elapsed_ = 0;
}

Environment::Environment(std::string file_path) {
  std::ifstream is(file_path);
  if (!is.is_open()) {
    throw std::invalid_argument("The file does not exists!");
  }
  std::string str;
  // Loop through the file to obtain the first integer. This is done to ignore
  // any text present at the beginning of the file
  while (!is.eof()) {
    std::getline(is, str);
    try {
      length_ = stoi(str);
    } catch (std::invalid_argument& e) {
      continue;
    }
    break;
  }
  try {
    is >> height_;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    is >> length_of_day_;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    size_t num_starting_organisms;
    is >> num_starting_organisms;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    double starting_speed;
    is >> starting_speed;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    double starting_size;
    is >> starting_size;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    speeds_ = std::vector<double>(num_starting_organisms, starting_speed);
    sizes_ = std::vector<double>(num_starting_organisms, starting_size);
    double max_energy;
    is >> max_energy;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    Organism::SetMaximumEnergy(max_energy);
    double surv_threshold;
    is >> surv_threshold;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    Organism::SetSurvivabilityThreshold(surv_threshold);
    double replicate_threshold;
    is >> replicate_threshold;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    Organism::SetReplicationThreshold(replicate_threshold);
    double speed_gene_trans;
    is >> speed_gene_trans;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    double speed_gene_change;
    is >> speed_gene_change;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    Organism::SetSpeedGene(speed_gene_trans, speed_gene_change);
    double size_gene_trans;
    is >> size_gene_trans;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    double size_gene_change;
    is >> size_gene_change;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    Organism::SetSizeGene(size_gene_trans, size_gene_change);
    is >> num_food_;
    if (is.eof()) {
      throw std::invalid_argument("File is of wrong format");
    }
    is >> total_calories_;
    is.close();
    AddFood();
    AddOrganisms(num_starting_organisms, starting_speed, starting_size);
    ResetOrganisms();
    population_.push_back(num_starting_organisms);
    time_elapsed_ = 0;
  } catch (std::exception& e) {
    throw e;
  }
}

void Environment::AddFood() {
  for (size_t i = 0; i < num_food_; i++) {
    double pos_x = rand() % (length_ / 2) + (length_ / 4);
    double pos_y = rand() % (height_ / 2) + (height_ / 4);
    glm::vec2 pos(pos_x, pos_y);
    food_.push_back(Food(pos, (total_calories_ / num_food_)));
  }
}

void Environment::AddOrganisms(size_t num_organisms, double speed,
                               double size) {
  speeds_ = std::vector<double>(num_organisms, speed);
  sizes_ = std::vector<double>(num_organisms, size);
  for (size_t i = 0; i < num_organisms; i++) {
    organisms_.push_back(Organism(speed, size));
  }
}

void Environment::RemoveDeadOrganisms() {
  for (size_t i = 0; i < organisms_.size(); i++) {
    if (!organisms_[i].WillSurvive()) {
      organisms_.erase(organisms_.begin() + i);
      speeds_.erase(speeds_.begin() + i);
      sizes_.erase(sizes_.begin() + i);
      i--;
    }
  }
}

void Environment::AddNewOrganisms() {
  for (const Organism& organism : organisms_) {
    if (organism.WillReplicate()) {
      Organism offspring = organism.Replicate();
      organisms_.push_back(offspring);
      speeds_.push_back(offspring.speed());
      sizes_.push_back(offspring.size());
    }
  }
}

void Environment::RemoveRandomOrganisms() {
  double base_probability =
      (double) organisms_.size() / (organisms_.size() + 1);
  for (size_t i = 0; i < organisms_.size(); i++) {
    if (((double)rand() / (double)RAND_MAX) <=
        (base_probability / organisms_[i].size())) {
      organisms_.erase(organisms_.begin() + i);
      speeds_.erase(speeds_.begin() + i);
      sizes_.erase(sizes_.begin() + i);
      i--;
    }
  }
}

void Environment::ResetOrganisms() {
  for (Organism& organism : organisms_) {
    int num_wall = rand() % 4;
    glm::vec2 pos;
    // Generate a random position for the organism on the border of the
    // environment
    switch (num_wall) {
      case 0:
        pos.x = organism.size();
        pos.y = organism.size() + ((height_ - (2 * organism.size())) *
                                      ((double)rand() / (double)RAND_MAX));
        break;
      case 1:
        pos.x = length_ - organism.size();
        pos.y = organism.size() + ((height_ - (2 * organism.size())) *
                                      ((double)rand() / (double)RAND_MAX));
        break;
      case 2:
        pos.y = organism.size();
        pos.x = organism.size() + ((length_ - (2 * organism.size())) *
                                  ((double)rand() / (double)RAND_MAX));
        break;
      case 3:
        pos.y = height_ - organism.size();
        pos.x = organism.size() + ((length_ - (2 * organism.size())) *
                                  ((double)rand() / (double)RAND_MAX));
        break;
    }
    organism.ResetForDay(pos);
  }
}

void Environment::Reset() {
  food_.clear();
  AddFood();
  RemoveDeadOrganisms();
  AddNewOrganisms();
  RemoveRandomOrganisms();
  ResetOrganisms();
  population_.push_back(organisms_.size());
  time_elapsed_ = 0;
  days_++;
}

void Environment::Update() {
  if (IsEndOfDay()) {
    Reset();
    return;
  }

  for (Organism& organism : organisms_) {
    organism.Update(length_, height_, food_);
    for (size_t i = 0; i < food_.size(); i++) {
      if (organism.Eat(food_[i])) {
        food_.erase(food_.begin() + i);
      }
    }
  }
  time_elapsed_++;
}
}// namespace naturalselection