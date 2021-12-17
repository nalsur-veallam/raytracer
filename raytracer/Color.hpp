#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

struct Color {
  double r, g, b;

  static Color Default();
};

std::ostream& operator<<(std::ostream& out, const Color& color);

#endif RAYTRACER_COLOR_HPP
