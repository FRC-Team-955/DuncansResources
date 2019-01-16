#pragma once
#include <vec2.hpp>

using namespace TinyVec;

float spline_f(float a, float b, float c, float d, float j);
Vec2 spline(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j);
Vec2 spline_deriv(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j);
Vec2 spline_deriv_sq(Vec2 a, Vec2 b, Vec2 c, Vec2 d, float j);
