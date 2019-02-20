#pragma once
#include <motion_state.hpp>
#include <algorithm>

using namespace TinyVec;

namespace TankDrive {
    struct TankOutput {
        float left_wheel_velocity;
        Vec2 left_wheel_position;
        float right_wheel_velocity;
        Vec2 right_wheel_position;
    };

	//Derivative of the above (Over dj)
	float velocity_magnitude_derivative (Vec2 velocity);

	//The change in position of the unit vector above over dj
	Vec2 perpendicular_unit_vector_derivative (Vec2 velocity, Vec2 acceleration);

    // Perpendicular to this vector
	Vec2 perpendicular_to(Vec2 input);

    float evaluate(
            ParametricOutput parametric, // Parametric input
            TankOutput& output, // Output struct
            float max_velocity, // Max change in position over delta time
            float dt, // Delta time
            float wheel_distance); // How far apart the wheels are
}
