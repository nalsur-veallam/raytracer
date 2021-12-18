#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

struct Color {
  double r, g, b;

  static Color Default();
}; // TODO: more operators

Color operator+(Color a, Color b);

Color operator*(Color a, double c);

std::ostream& operator<<(std::ostream& out, const Color& color);

#endif
