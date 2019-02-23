#pragma once
#include <vec2.hpp>

struct MotionState {
    TinyVec::Vec2 position; //f(index)
    TinyVec::Vec2 velocity; //f'(index)
    TinyVec::Vec2 acceleration; //f''(index)
};
