#include <spline.hpp>

Vec2 spline(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j) {
  return (powf(1 - j, 3.0) * a) + (3.0 * powf(1 - j, 2.0) * j * b) +
         (3.0 * (1 - j) * powf(j, 2.0) * c) + (powf(j, 3.0) * d);
}

Vec2 spline_deriv(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j) {
  return (3.0 * powf(1 - j, 2.0) * (b - a)) + (6.0 * (1 - j) * j * (c - b)) +
         (3.0 * powf(j, 2.0) * (d - c));
}

Vec2 spline_deriv_sq(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j) {
  return (6.0 * (1 - j) * (c - (2.0 * b) + a)) +
         (6.0 * j * (d - (2.0 * c) + b));
}

float spline_f(float a, float b, float c, float d, float j) {
  return (powf(1 - j, 3.0) * a) + (3.0 * powf(1 - j, 2.0) * j * b) +
         (3.0 * (1 - j) * powf(j, 2.0) * c) + (powf(j, 3.0) * d);
}
