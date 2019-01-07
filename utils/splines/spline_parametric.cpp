#include <spline_parametric.hpp>

ParametricOutput spline_parametric(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j) {
  return {
      spline(a, b, c, d, j), 
      spline_deriv(a, b, c, d, j),
      spline_deriv_sq(a, b, c, d, j)
  };
}
