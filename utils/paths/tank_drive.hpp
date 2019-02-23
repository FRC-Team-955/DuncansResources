#pragma once
#include <algorithm>
#include <motion_state.hpp>

namespace TankDrive {
    using namespace TinyVec;

    struct TankOutput {
        float left_wheel_velocity;
        Vec2 left_wheel_position;
        float right_wheel_velocity;
        Vec2 right_wheel_position;
        float change_in_index;
    };

    // Derivative of the above (Over dj)
    float velocity_magnitude_derivative(Vec2 velocity, Vec2 acceleration);

    // The change in position of the unit vector above over dj
    Vec2 perpendicular_unit_vector_derivative(Vec2 velocity, Vec2 acceleration);

    // Perpendicular to this vector
    Vec2 perpendicular_to(Vec2 input);

    void evaluate(MotionState motion_path,  // Parametric input
            TankOutput& output,       // Output struct
            float max_velocity,     // Max change in position over delta time
            float time_delta,       // Delta time
            float wheel_distance);  // How far apart the wheels are
}  // namespace TankDrive
