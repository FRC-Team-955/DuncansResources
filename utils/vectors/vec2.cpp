#include <vec2.hpp>

using namespace TinyVec;

Vec2::Vec2(float x, float y) : x(x), y(y){};
Vec2::Vec2(float k) : x(k), y(k){};
Vec2::Vec2() : Vec2(0.0) {};
Vec2 Vec2::operator+(Vec2 other) { return Vec2(x + other.x, y + other.y); }
Vec2 Vec2::operator-(Vec2 other) { return Vec2(x - other.x, y - other.y); }
Vec2 Vec2::operator*(float scalar) { return Vec2(x * scalar, y * scalar); }
Vec2 Vec2::operator/(float scalar) { return Vec2(x / scalar, y / scalar); }
float Vec2::dot(Vec2 other) { return (other.x * this->x) + (other.y * this->y); }
float Vec2::magnitude() { return sqrt(this->dot(*this)); }
float Vec2::distance(Vec2 other) { return (*this - other).magnitude(); }
float Vec2::normalized() { return *this / this->magnitude(); }
Vec2 TinyVec::operator*(float lhs, Vec2 rhs) { return rhs * lhs; }
Vec2 TinyVec::operator+(float lhs, Vec2 rhs) { return rhs + lhs; }
