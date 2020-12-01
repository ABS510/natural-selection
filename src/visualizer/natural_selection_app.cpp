#include "visualizer/natural_selection_app.h"

namespace naturalselection {

NaturalSelectionApp::NaturalSelectionApp() : environment_display_(
  Environment(environment_length_, environment_height_, total_calories_,
  num_food_, num_organisms_, length_of_day_, init_speed_, init_size_),
  top_left_corner_) {
  Organism::SetSpeedGene(speed_gene_transfer_, speed_gene_max_);
  Organism::SetSizeGene(size_gene_transfer_, size_gene_max_);
  Organism::SetSurvivabilityThreshold(survivability_threshold_);
  Organism::SetReplicationThreshold(replication_threshold_);
  Organism::SetMaximumEnergy(max_energy_);

  ci::app::setWindowSize((int) kWindowSizeLength_, (int) kWindowSizeHeight_);
}

void NaturalSelectionApp::draw() {
  ci::gl::clear("black");
  environment_display_.Draw();
};

void NaturalSelectionApp::update() {
  environment_display_.Update();
}
}