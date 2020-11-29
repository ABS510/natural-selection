#include "core/environment.h"

namespace naturalselection {

Environment::Environment(int length, int height)
    : Environment(length, height, 1000, 30,
                  20, 240) {}

Environment::Environment(int length, int height, double total_calories,
                         int num_food, int num_starting_organisms)
    : Environment(length, height, total_calories, num_food,
                  num_starting_organisms, 240) {}

Environment::Environment(int length, int height, double total_calories,
                         int num_food, int num_starting_organisms,
                         int length_of_day)
    : Environment(length, height, total_calories, num_food,
                  num_starting_organisms, 240, 4, 10) {}

Environment::Environment(int length, int height, double total_calories,
                         int num_food, int num_starting_organisms,
                         int length_of_day, double starting_speed,
                         double starting_size)
    : length_(length) , height_(height), length_of_day_(length_of_day) {
  total_calories_ = total_calories;
  num_food_ = num_food;
  AddFood();
  AddOrganisms(num_starting_organisms, starting_speed, starting_size);
  ResetOrganisms();
  time_elapsed_ = 0;
}

void Environment::AddFood() {
  for (size_t i = 0; i < num_food_; i++) {
    double pos_x = rand() % (length_ / 2) + (length_ / 4);
    double pos_y = rand() % (height_ / 2) + (height_ / 4);
    glm::vec2 pos(pos_x, pos_y);
    food_.push_back(Food(pos, (total_calories_ / num_food_)));
  }
}

void Environment::AddOrganisms(int num_organisms, double speed, double size) {
  for (size_t i = 0; i < num_organisms; i++) {
    organisms_.push_back(Organism(speed, size));
  }
}

void Environment::RemoveDeadOrganisms() {
  for (size_t i = 0; i < organisms_.size(); i++) {
    if (!organisms_[i].WillSurvive()) {
      organisms_.erase(organisms_.begin() + i);
      i--;
    }
  }
}

void Environment::AddNewOrganisms() {
  for (const Organism& organism : organisms_) {
    if (organism.WillReplicate()) {
      organisms_.push_back(organism.Replicate());
    }
  }
}

void Environment::RemoveRandomOrganisms() {
  float base_probability = (double) organisms_.size() / (organisms_.size() + 1);
  for (size_t i = 0; i < organisms_.size(); i++) {
    if (((double)rand() / (double)RAND_MAX) <= (base_probability / organisms_[i].size())) {
      organisms_.erase(organisms_.begin() + i);
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
  time_elapsed_ = 0;
}

void Environment::Update() {
  if (time_elapsed_ >= length_of_day_) {
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