#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include <visualizer/environment_display.h>

using std::vector;
namespace naturalselection {

class NaturalSelectionApp : public ci::app::App {
 public:
  /**
   * Default constructor
   */
  NaturalSelectionApp();

  void draw() override;
  void update() override;

  const double kWindowSizeLength_ = 1200;
  const double kWindowSizeHeight_ = 750;
  const double kMargin_ = 100;

 private:
  // length of the environment
  const size_t environment_length_ = 600;
  // height of the environment
  const size_t environment_height_ = 600;
  // length of each day
  const int length_of_day_ = 240;
  // location of top-left corner of environment
  const glm::vec2 top_left_corner_ = glm::vec2(kMargin_, kMargin_);
  // initial number of organisms
  const int num_organisms_ = 4;
  // initial speed of organisms
  const double init_speed_ = 3;
  // initial size of organisms
  const double init_size_ = 10;
  // the energy of each organism
  const double max_energy_ = 3000;
  // the survivability threshold for organisms
  const double survivability_threshold_ = 150;
  // the replication threshold for organisms
  const double replication_threshold_ = 300;
  // the speed gene traits
  const double speed_gene_transfer_ = 30;
  const double speed_gene_max_ = 0.15;
  // the size gene traits
  const double size_gene_transfer_ = 30;
  const double size_gene_max_ = 0.1;

  // variables for food in the environment
  const int num_food_ = 50;
  const double total_calories_ = 5000;

  // The ContainerDisplay object to display the container with particles
  EnvironmentDisplay environment_display_;
};
} // namespace idealgas