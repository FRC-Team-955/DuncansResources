#include <tank_drive.hpp>

float TankDrive::evaluate(ParametricOutput parametric,
		TankDrive::TankOutput &output, float max_velocity,
		float dt, float wheel_distance) {

	// Position = center + (perpendicular vector * d)
	output.center_position = parametric.position;
	output.left_position =
		parametric.position +
		(wheel_distance * parametric.perpendicular_unit_vector_xy());
	output.right_position =
		parametric.position -
		(wheel_distance * parametric.perpendicular_unit_vector_xy());

	// How far in position we expect to go over dj
	Vec2 chage_pos_left =
		(parametric.velocity) +
		(wheel_distance * parametric.perpendicular_unit_vector_derivative_xy());
	Vec2 chage_pos_right =
		(parametric.velocity) -
		(wheel_distance * parametric.perpendicular_unit_vector_derivative_xy());

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
	output.motion.velocity_left = dp_left / dt;
	output.motion.velocity_right = dp_right / dt;

	// Increment positions
	output.motion.position_left += dp_left;
	output.motion.position_right += dp_right;

	// Robot heading
	output.robot_direction = parametric.direction_xy();

	// We are turning too hard, one side will have to reverse
	// Determined by the normal of each wheel's trajectory not being within 90
	// degrees of the trajectory of the robot center (It's reversing)
	float direction_left = atan2(chage_pos_left.y, chage_pos_left.x);
	float direction_right = atan2(chage_pos_right.y, chage_pos_right.x);
	if (parametric.velocity.dot(chage_pos_left) < 0)
		output.motion.velocity_left *= -1.0;

	if (parametric.velocity.dot(chage_pos_right) < 0)
		output.motion.velocity_right *= -1.0;

	// How far along the spline we advanced
	return dj;
}
