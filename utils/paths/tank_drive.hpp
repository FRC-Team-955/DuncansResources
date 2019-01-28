#pragma once
#include <parametric_output.hpp>
#include <algorithm>

namespace TankDrive {
    struct TankDriveMotionUnit {
        float position_left; // Distance travelled by left wheel
        float velocity_left; // Velocity of left wheel
        float position_right; // Distance travelled by right wheel
        float velocity_right; // Velocity of right wheel
    };

    struct TankOutput {
        TankDriveMotionUnit motion; // Motion information
        Vec2 left_position; // 2D position of left wheel
        Vec2 right_position; // 2D position of right wheel
        Vec2 center_position; // 2D position of robot center
        float robot_direction; // Direction (in radians) of the robot
    };

    float evaluate(
            ParametricOutput parametric, // Parametric input
            TankOutput& output, // Output struct
            float max_velocity, // Max change in position over delta time
            float dt, // Delta time
            float wheel_distance); // How far apart the wheels are
}
