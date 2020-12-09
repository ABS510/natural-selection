#include "visualizer/natural_selection_app.h"

namespace naturalselection {

NaturalSelectionApp::NaturalSelectionApp() : environment_display_(
  Environment(file_path_),top_left_corner_),
  graph_top_left_corner_(2 * kMargin_ +
             environment_display_.environment().length(), kMargin_),
  line_graph_(graph_top_left_corner_, graph_size_, graph_size_, 8, "days",
                                                         "population"),
  speed_histogram_(graph_top_left_corner_ + glm::vec2(0, graph_size_ + 30),
                   graph_size_, graph_size_, "speed","frequency %", 15,
                   environment_display_.num_organisms(),8),
  size_histogram_(graph_top_left_corner_ + glm::vec2(0, 2 * graph_size_ + 60),
                   graph_size_, graph_size_, "size","frequency %", 15,
                   environment_display_.num_organisms(),8) {
  ci::app::setWindowSize((int) kWindowSizeLength_, (int) kWindowSizeHeight_);
}

void NaturalSelectionApp::draw() {
  ci::gl::clear("black");
  environment_display_.Draw();
  line_graph_.DrawGraph(environment_display_.population(), "white", "white");
  speed_histogram_.DrawHistogram(environment_display_.speeds(), "white",
                                   "white", 2);
  size_histogram_.DrawHistogram(environment_display_.sizes(), "white",
                                  "white", 2);
}

void NaturalSelectionApp::update() {
  environment_display_.Update();
  speed_histogram_.set_max_x(
      *max_element(environment_display_.speeds().begin(),
                   environment_display_.speeds().end()));
  speed_histogram_.set_max_y(environment_display_.num_organisms());
  size_histogram_.set_max_x(
      *max_element(environment_display_.sizes().begin(),
                   environment_display_.sizes().end()));
  size_histogram_.set_max_y(environment_display_.num_organisms());
}
}