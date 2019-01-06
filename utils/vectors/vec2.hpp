#pragma once
#include <cmath>

namespace TinyVec {
    struct Vec2 {
        public:
            float x, y;
            Vec2(float x, float y) : x(x), y(y){};
            Vec2(float k) : x(k), y(k){};
            Vec2 operator+(Vec2 other) { return Vec2(x + other.x, y + other.y); }
            Vec2 operator-(Vec2 other) { return Vec2(x - other.x, y - other.y); }
            Vec2 operator*(float scalar) { return Vec2(x * scalar, y * scalar); }
            Vec2 operator/(float scalar) { return Vec2(x / scalar, y / scalar); }
            float dot(Vec2 other) { return (other.x * this->x) + (other.y * this->y); }
            float magnitude() { return sqrt(this->dot(*this)); }
            float distance(Vec2 other) { return (*this - other).magnitude(); }
    };

    Vec2 operator*(float lhs, Vec2 rhs) { return rhs * lhs; }
    Vec2 operator+(float lhs, Vec2 rhs) { return rhs + lhs; }
    Vec2 lerp(Vec2 a, Vec2 b, float i) { return a * (1.0 - i) + (b * i); };
}
