#include <visualizer/histogram.h>
#include "cinder/gl/gl.h"

using glm::vec2;

namespace naturalselection {

Histogram::Histogram(glm::vec2 top_left_corner, size_t length, size_t height,
                     std::string x_label, std::string y_label, double max_x,
                     double max_y, size_t num_bars)
    : top_left_corner_(top_left_corner), length_(length), height_(height) {
  x_axis_label_ = x_label;
  y_axis_label_ = y_label;
  max_x_ = max_x;
  max_y_ = max_y;
  num_bars_ = num_bars;
  str_pixel_buffer_ = 10;
}

Histogram::Histogram(glm::vec2 top_left_corner, size_t length, size_t height,
                     std::string x_label, std::string y_label, double max_x,
                     double max_y, size_t num_bars, int str_pixel_buffer)
    : top_left_corner_(top_left_corner), length_(length), height_(height) {
  x_axis_label_ = x_label;
  y_axis_label_ = y_label;
  max_x_ = max_x;
  max_y_ = max_y;
  num_bars_ = num_bars;
  str_pixel_buffer_ = str_pixel_buffer;
}

void Histogram::DrawHistogram(const std::vector<double>& x_data,
                              ci::Color8u bar_color, ci::Color8u axis_color,
                              size_t x_scale_precision) {

  max_x_ = *max_element(x_data.begin(), x_data.end());
  DrawAxes(axis_color, x_scale_precision);

  int bar_width = length_ / num_bars_;
  for(size_t i = 0; i < num_bars_; i++) {
    // Calculate bar height
    int freq = 0;
    for (double data : x_data) {
      if (GetBin(data) == i) {
        freq++;
      }
    }
    int bar_height = (freq * height_) / max_y_;
    // Draw bar
    ci::gl::color(bar_color);
    ci::Rectf bar(top_left_corner_ + vec2(bar_width * i, height_ - bar_height),
                  top_left_corner_ + vec2(bar_width * (i + 1), height_));
    ci::gl::drawSolidRect(bar);
  }
}

void Histogram::DrawAxes(ci::Color8u axis_color, size_t x_scale_precision) {
  ci::gl::color(axis_color);
  // Drawing x-axis
  ci::gl::drawLine(top_left_corner_,
                   top_left_corner_ + vec2(0, height_));
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
  for (size_t i = 0; i <= 4; i++) {
    ci::gl::drawStringCentered(std::to_string(i * 25),top_left_corner_ +
                  vec2(-str_pixel_buffer_, (4 - i) * height_ / 4));
  }

  // Displaying the scale on the x-axis
  int bar_width = length_ / num_bars_;
  for(size_t i = 0; i < num_bars_ + 1; i++) {
    double lower_bound = i * (max_x_ / num_bars_);
    // Display x-axis scale
    std::stringstream x_axis_scale;
    x_axis_scale << std::setprecision(x_scale_precision) << lower_bound;
    ci::gl::drawStringCentered(
        x_axis_scale.str(),
        top_left_corner_ + vec2(bar_width * i, height_ + str_pixel_buffer_));
  }
}

int Histogram::GetBin(double value) {
  int bin = (int) (value / (max_x_ / num_bars_));
  if (bin < 0) {
    return 0;
  }
  if (bin >= num_bars_) {
    return num_bars_ - 1;
  }
  return bin;
}
} // namespace natural selection
