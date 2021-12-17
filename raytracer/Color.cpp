#include <iostream>
#include "Color.hpp"

Color Color::Default() {
  return {0, 1, 0};
}

std::ostream& operator<<(std::ostream& out, const Color& color) {
  out << color.r << " " << color.g << " " << color.b;
  return out;
}
