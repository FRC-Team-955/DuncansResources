#pragma once
#include <vec2.hpp>

using namespace TinyVec;

struct ParametricOutput {
	Vec2 position; //f(index)
	Vec2 velocity; //f'(index)
	Vec2 acceleration; //f''(index)

	//Derivative of the above (Over dj)
	float velocity_magnitude_derivative_xy ();

	//Angle of the tangent line relative to the origin
	float direction_xy();;

	//x'(j)^2 + y'(j)^2
	float sum_derivative_squares_xy ();

	//Normalized perpendicular vector to the tangent line
	Vec2 perpendicular_unit_vector_xy ();

	//The change in position of the unit vector above over dj
	Vec2 perpendicular_unit_vector_derivative_xy ();

	//d(slope)/dj
	float change_in_slope();

	//d(tan^-1 (y'(j)/x'(j))) / dj
	float change_in_angle();

    // Perpendicular to this vector
	Vec2 normal_to(Vec2 input);
};
