#include "visualizer/line_graph.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace naturalselection {

LineGraph::LineGraph(glm::vec2 top_left_corner, size_t length, size_t height,
                     size_t x_scale, size_t y_scale, std::string x_label,
                     std::string y_label)
    : LineGraph(top_left_corner, length, height, x_scale, y_scale,
                x_label, y_label, 10) {}

LineGraph::LineGraph(glm::vec2 top_left_corner, size_t length, size_t height,
                     size_t x_scale, size_t y_scale, std::string x_label,
                     std::string y_label, int str_pixel_buffer)
    : top_left_corner_(top_left_corner), length_(length), height_(height) {
  x_axis_label_ = x_label;
  y_axis_label_ = y_label;
  x_scale_ = x_scale;
  y_scale_ = y_scale;
  str_pixel_buffer_ = str_pixel_buffer;
}

void LineGraph::DrawGraph(const std::vector<int>& data,
                          ci::Color8u line_color, ci::Color8u axis_color) {

  int max_y = *max_element(data.begin(), data.end());
  DrawAxes(axis_color, data.size(), max_y);
  double width = ((double) length_) / data.size();
  for(size_t i = 1; i < data.size(); i++) {
    vec2 current_point(i * width, height_ - (data[i] * height_) / max_y);
    vec2 prev_point((i - 1) * width,
                    height_ - (data[i - 1] * height_) / max_y);
    // Draw line
    ci::gl::color(line_color);
    ci::gl::drawLine(top_left_corner_ + prev_point,
                     top_left_corner_ + current_point);
  }
}

void LineGraph::DrawAxes(ci::Color8u axis_color, size_t num_values, int max_y) {
  ci::gl::color(axis_color);
  // Drawing x-axis
  ci::gl::drawLine(top_left_corner_,top_left_corner_ + vec2(0, height_));
  // Drawing y-axis
  ci::gl::drawLine(top_left_corner_ + vec2(0, height_),
                   top_left_corner_ + vec2(length_, height_));

  // Display x-axis label text
  ci::gl::drawStringCentered(x_axis_label_, top_left_corner_ +
          vec2(length_ / 2, height_ + 2 * str_pixel_buffer_));

  vec2 y_axis_text_pos = top_left_corner_ +
                         vec2(- 3 * str_pixel_buffer_, height_ / 2);
  // Rotate the text of y-axis label by 90 degrees
  ci::gl::translate(y_axis_text_pos);
  ci::gl::rotate(-M_PI/2);
  ci::gl::drawStringCentered(y_axis_label_, vec2(0,0));
  ci::gl::rotate(M_PI/2);
  ci::gl::translate(-y_axis_text_pos);

  // Displaying the scale on the y-axis
  for (size_t i = 0; i <= y_scale_; i++) {
    int y_val = (i * max_y) / y_scale_;
    int height = (y_val * height_) / max_y;
    ci::gl::drawStringCentered(std::to_string(y_val),top_left_corner_ +
                     vec2(-str_pixel_buffer_, height_ - height));
  }

  // Displaying the scale on the x-axis
  int num_x_scale_div = x_scale_;
  if(num_values < x_scale_) {
    num_x_scale_div = num_values;
  }
  double width = ((double) length_) / num_x_scale_div;
  for(size_t i = 1; i <= num_x_scale_div; i++) {
    int x_data = (i * num_values) / num_x_scale_div;
    ci::gl::drawStringCentered(std::to_string(x_data), top_left_corner_ +
        vec2(width * (i - 1), height_ + str_pixel_buffer_));
    if (i == num_x_scale_div && num_values < x_scale_) {
      ci::gl::drawStringCentered(std::to_string(x_data + 1), top_left_corner_ +
        vec2(width * (i), height_ + str_pixel_buffer_));
    }
  }
}
} // namespace naturalselection
