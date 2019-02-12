#include <parametric_output.hpp>

float ParametricOutput::velocity_magnitude_derivative_xy () {
	return acceleration.dot(velocity) / velocity.magnitude();
}

float ParametricOutput::direction_xy () {
	return std::atan2(velocity.y, velocity.x);
}

float ParametricOutput::sum_derivative_squares_xy () {
	return velocity.dot(velocity);
}

Vec2 ParametricOutput::perpendicular_unit_vector_xy () {
	return normal_to(velocity) / velocity.magnitude();
}

Vec2 ParametricOutput::perpendicular_unit_vector_derivative_xy () {
	return ((normal_to(acceleration)) * velocity.magnitude() -
			(normal_to(velocity)) * velocity_magnitude_derivative_xy())
		/ sum_derivative_squares_xy();
}

float ParametricOutput::change_in_slope() {
	return ((acceleration.y * velocity.x) - (acceleration.x * velocity.y)) / powf(velocity.x, 2.0);
}

float ParametricOutput::change_in_angle() {
	return (1.0 / (1.0 + powf(velocity.y / velocity.x, 2.0))) * change_in_slope();
}

Vec2 ParametricOutput::normal_to(Vec2 input) {
	return Vec2(-input.y, input.x);
}
