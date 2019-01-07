#pragma once
#include <parametric_output.hpp>
#include <algorithm>

namespace TankDrive {
    struct TankDriveMotionUnit {
        float position_left;
        float velocity_left;
        float position_right;
        float velocity_right;
    };

    struct TankOutput {
        TankDriveMotionUnit motion;
        Vec2 left_position;
        Vec2 right_position;
        Vec2 center_position;
        float robot_direction;
    };

    float evaluate(
            ParametricOutput parametric,
            TankOutput& output,
            float max_velocity,
            float dt,
            float wheel_distance);
}
