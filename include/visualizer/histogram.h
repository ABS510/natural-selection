#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

namespace naturalselection {

/**
 * This class represent a histogram
 */
class Histogram {
 public:
  /**
   * Constructor to initialize histogram with each instance variable
   * @param top_left_corner Top left corner of histogram
   * @param length Length of the histogram
   * @param height Height of the histogram
   * @param x_label X-axis label of the histogram
   * @param y_label Y-axis label of the histogram
   * @param max_x Maximum x-value to be displayed by the histogram
   * @param max_y Maximum y-value to be displayed by the histogram
   * @param num_bars Number of bars of the histogram
   */
  Histogram(glm::vec2 top_left_corner, size_t length, size_t height,
            std::string x_label, std::string y_label,
            double max_x, double max_y, size_t num_bars);

  /**
   * Constructor to initialize histogram with each instance variable
   * @param top_left_corner Top left corner of histogram
   * @param length Length of the histogram
   * @param height Height of the histogram
   * @param x_label X-axis label of the histogram
   * @param y_label Y-axis label of the histogram
   * @param max_x Maximum x-value to be displayed by the histogram
   * @param max_y Maximum y-value to be displayed by the histogram
   * @param num_bars Number of bars of the histogram
   * @param str_pixel_buffer The pixel buffer for displaying the string labels
   * for the x and y axis
   */
  Histogram(glm::vec2 top_left_corner, size_t length, size_t height,
            std::string x_label, std::string y_label, double max_x,
            double max_y, size_t num_bars, int str_pixel_buffer);
  /**
   * Function to draw the histogram
   * @param data- The data of the histogram to be displayed
   * @param bar_color- The color of the bars of the graph
   * @param axis_color- The color of the axes
   * @param x_scale_precision- The number of significant figures to display for
   * the x-axis scale
   * displayed on the x-axis scale
   */
  void DrawHistogram(const std::vector<double>& data, ci::Color8u bar_color,
                     ci::Color8u axis_color, size_t x_scale_precision);

  /**
   * Getter method for top left corner
   * @return top_left_corner_
   */
  const glm::vec2& top_left_corner() const {
    return top_left_corner_;
  }

  /**
  * Setter method for max_x_
  * @param max_x- the value to which max_x_ will be set
  */
  void set_max_x(double max_x) {
    max_x_ = max_x;
  }

  /**
  * Setter method for max_y_
  * @param max_y- the value to which max_y_ will be set
  */
  void set_max_y(size_t max_y) {
    max_y_ = max_y;
  }

  /**
   * Function to obtain the bin to which a value should belong to
   * @param value The value to be placed in the bin
   * @return an int from 0 to num_bars_ - 1, corresponding to the bin
   */
  int GetBin(double value);

 private:
  // Position of the top left corner of the histogram
  const glm::vec2 top_left_corner_;
  // Length of histogram
  const size_t length_;
  // Height pf the histogram
  const size_t height_;
  // X-axis label
  std::string x_axis_label_;
  // Y-axis label
  std::string y_axis_label_;
  // Maximum x-axis value of graph
  double max_x_;
  // Maximum y-axis value of the graph
  size_t max_y_;
  // Number of bars of the histogram
  size_t num_bars_;
  // Pixel buffer between axis and labels
  int str_pixel_buffer_;

  /**
   * Helper function to draw the x and y axis, as well as their labels & scales
   * @param axis_color- color of the axes
   * @param x_scale_precision- The number of significant figures to display for
   * the x-axis scale
   */
  void DrawAxes(ci::Color8u axis_color, size_t x_scale_precision);

};
} // namespace naturalselection