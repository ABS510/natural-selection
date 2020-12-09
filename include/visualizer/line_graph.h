#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

namespace naturalselection {

/**
 * This class represent a line graph
 */
class LineGraph {
 public:
  /**
   * Constructor to initialize line graph with each instance variable
   * @param top_left_corner Top left corner of line graph
   * @param length Length of the line graph
   * @param height Height of the line graph
   * @param x_scale The number of x scale values to be displayed on the x-axis
   * @param y_scale The number of y scale values to be displayed on the y-axis
   * @param x_label X-axis label of the line graph
   * @param y_label Y-axis label of the line graph
   */
  LineGraph(glm::vec2 top_left_corner, size_t length, size_t height,
            size_t x_scale, size_t y_scale, std::string x_label,
            std::string y_label);

  /**
   * Constructor to initialize line graph with each instance variable
   * @param top_left_corner Top left corner of line graph
   * @param length Length of the line graph
   * @param height Height of the line graph
   * @param x_scale The number of x scale values to be displayed on the x-axis
   * @param y_scale The number of y scale values to be displayed on the y-axis
   * @param x_label X-axis label of the line graph
   * @param y_label Y-axis label of the line graph
   * @param str_pixel_buffer The pixel buffer for displaying the string labels
   * for the x and y axis
   */
  LineGraph(glm::vec2 top_left_corner, size_t length, size_t height,
            size_t x_scale, size_t y_scale, std::string x_label,
            std::string y_label, int str_pixel_buffer);
  /**
   * Function to draw the line graph
   * @param data- The data of the line graph to be displayed
   * @param line_color- The color of the bars of the graph
   * @param axis_color- The color of the axes
   */
  void DrawGraph(const std::vector<int>& data, ci::Color8u line_color,
                 ci::Color8u axis_color);

  /**
   * Getter method for top left corner
   * @return top_left_corner_
   */
  const glm::vec2& top_left_corner() const {
    return top_left_corner_;
  }

 private:
  // Position of the top left corner of the line graph
  glm::vec2 top_left_corner_;
  // Length of line graph
  size_t length_;
  // Height pf the line graph
  size_t height_;
  // X-axis label
  std::string x_axis_label_;
  // Y-axis label
  std::string y_axis_label_;
  // Number of values to be displayed on the x-axis scale
  size_t x_scale_;
  // Number of values to be displayed on the y-axis scale
  size_t y_scale_;
  // Pixel buffer between axis and labels
  int str_pixel_buffer_;

  /**
   * Helper function to draw the x and y axis, as well as their labels & scales
   * @param axis_color- color of the axes
   * @param x_scale_precision- The number of significant figures to display for
   * the x-axis scale
   */
  void DrawAxes(ci::Color8u axis_color, size_t num_values, int max_y);
};
} // namespace naturalselection