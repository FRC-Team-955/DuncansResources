#pragma once
#include <cmath>

namespace TinyVec {
    struct Vec2 {
        public:
            float x, y;
            Vec2(float x, float y);
            Vec2(float k);
            Vec2();
            Vec2 operator+(Vec2 other);
            Vec2 operator-(Vec2 other);
            Vec2 operator*(float scalar);
            Vec2 operator/(float scalar);
            float dot(Vec2 other);
            float magnitude();
            float distance(Vec2 other);
            Vec2 normalized();
    };

    Vec2 operator*(float lhs, Vec2 rhs);
    Vec2 operator+(float lhs, Vec2 rhs);
}  // namespace TinyVec
