#include <tank_drive.hpp>

void TankDrive::evaluate(MotionState current_state,
		TankDrive::TankOutput &output, float max_velocity,
		float dt, float wheel_distance) {

	// Position = center + (perpendicular vector * d)
	output.left_position =
	current_state.position - 
    (perpendicular_to(current_state.velocity).normalized() * d);

	output.rightt_position =
	current_state.position + 
    (perpendicular_to(current_state.velocity).normalized() * d);

	// How far in position we expect to go over dj
	Vec2 chage_pos_left =
		(current_state.velocity) -
		(wheel_distance * perpendicular_unit_vector_derivative(current_state.velocity, current_state.acceleration));

	Vec2 chage_pos_left =
		(current_state.velocity) +
		(wheel_distance * perpendicular_unit_vector_derivative(current_state.velocity, current_state.acceleration));

	// Magnitude of change in position of the above over dj
	float dp_dj_left = chage_pos_left.magnitude();
	float dp_dj_right = chage_pos_right.magnitude();

	// Find dj for the time step
	float largest_dp_dj = std::max(dp_dj_left, dp_dj_right);
	float max_dp = max_velocity * dt;
	float dj = (max_dp / largest_dp_dj);

	// Distances travelled per dt
	float dp_left = (dj * dp_dj_left);
	float dp_right = (dj * dp_dj_right);

	// Assign velocities
	output.left_wheel_velocity = dp_left / dt;
	output.right_wheel_velocity = dp_right / dt;

	// Check whether each wheel is travelling in a different direction from the
    // center of the robot. If so, reverse the wheel.
	if (current_state.velocity.dot(chage_pos_left) < 0)
		output.motion.velocity_left *= -1.0;

	if (current_state.velocity.dot(chage_pos_right) < 0)
		output.motion.velocity_right *= -1.0;

	// How far along the spline we advanced
	return dj;
}

float TankDrive::velocity_magnitude_derivative (Vec2 velocity) {
	return acceleration.dot(velocity) / velocity.magnitude();
}

Vec2 TankDrive::perpendicular_unit_vector_derivative (Vec2 velocity, Vec2 acceleration) {
	return ((perpendicular_to(acceleration)) * velocity.magnitude() -
			(perpendicular_to(velocity)) * velocity_magnitude_derivative())
		/ velocity.dot(velocity);
}

Vec2 TankDrive::perpendicular_to(Vec2 input) {
	return Vec2(-input.y, input.x);
}
