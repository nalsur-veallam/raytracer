#include <iostream>
#include "Color.hpp"

Color Color::Default() {
  return {0, 0, 0};
}

std::ostream& operator<<(std::ostream& out, const Color& color) {
  out << color.r << " " << color.g << " " << color.b;
  return out;
}

Color operator+(Color a, Color b) {
  return {a.r + b.r, a.g + b.g, a.b + b.b};
}

Color operator*(Color a, double c) {
  return {a.r * c, a.g * c, a.b * c};
}
