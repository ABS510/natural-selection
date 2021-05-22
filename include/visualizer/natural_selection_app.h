#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include <visualizer/environment_display.h>
#include <visualizer/line_graph.h>
#include <visualizer/histogram.h>

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

  const double kWindowSizeLength_ = 1000;
  const double kWindowSizeHeight_ = 800;
  const double kMargin_ = 50;

 private:
  // File path to load the environment
  std::string file_path_ = "data/setup1";
  // Top left corner of the environment
  const glm::vec2 top_left_corner_ = glm::vec2(kMargin_, kMargin_);
  // The length and height of each graph
  const size_t graph_size_ = 200;
  // The ContainerDisplay object to display the container with particles
  EnvironmentDisplay environment_display_;
  // Top left corner of line graph
  glm::vec2 graph_top_left_corner_;
  // The line graph of the population
  LineGraph line_graph_;
  // The histogram for speed distribution
  Histogram speed_histogram_;
  // The histogram for size distribution
  Histogram size_histogram_;
};
} // namespace idealgas