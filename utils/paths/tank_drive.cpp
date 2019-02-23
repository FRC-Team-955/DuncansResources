#include <tank_drive.hpp>

namespace TankDrive {
    void evaluate(MotionState motion_path,
            TankOutput& output,
            float max_velocity,
            float time_delta,
            float wheel_distance) {
        // Position = center + (perpendicular vector * d)
        output.left_wheel_position =
            motion_path.position -
            (perpendicular_to(motion_path.velocity).normalized() * wheel_distance);

        output.right_wheel_position =
            motion_path.position +
            (perpendicular_to(motion_path.velocity).normalized() * wheel_distance);

        // How far in position we expect to go over change_in_index
        Vec2 chage_pos_left =
            (motion_path.velocity) -
            (wheel_distance * perpendicular_unit_vector_derivative(
            motion_path.velocity, motion_path.acceleration));

        Vec2 chage_pos_right =
            (motion_path.velocity) +
            (wheel_distance * perpendicular_unit_vector_derivative(
            motion_path.velocity, motion_path.acceleration));

        // Magnitude of change in position of the above over change_in_index
        float dp_dj_left = chage_pos_left.magnitude();
        float dp_dj_right = chage_pos_right.magnitude();

        // Find largest change_in_index for the time step (fastest moving wheel)
        float largest_dp_dj = std::max(dp_dj_left, dp_dj_right);
        float max_dp = max_velocity * time_delta;
        float change_in_index = (max_dp / largest_dp_dj);

        // Distances travelled per time_delta
        float dp_left = (change_in_index * dp_dj_left);
        float dp_right = (change_in_index * dp_dj_right);

        // Assign velocities
        output.left_wheel_velocity = dp_left / time_delta;
        output.right_wheel_velocity = dp_right / time_delta;

        // Check whether each wheel is travelling in a different direction from the
        // center of the robot. If so, reverse the wheel.
        if (motion_path.velocity.dot(chage_pos_left) < 0)
            output.left_wheel_velocity *= -1.0;

        if (motion_path.velocity.dot(chage_pos_right) < 0)
            output.right_wheel_velocity *= -1.0;

        // Export change in index
        output.change_in_index = change_in_index;
    }

    float velocity_magnitude_derivative(Vec2 velocity, Vec2 acceleration) {
        return acceleration.dot(velocity) / velocity.magnitude();
    }

    Vec2 perpendicular_unit_vector_derivative(Vec2 velocity, Vec2 acceleration) {
        return ((perpendicular_to(acceleration)) * velocity.magnitude() -
                (perpendicular_to(velocity)) *
                velocity_magnitude_derivative(velocity, acceleration)) /
            velocity.dot(velocity);
    }

    Vec2 perpendicular_to(Vec2 input) {
        return Vec2(-input.y, input.x);
    }
}  // namespace TankDrive
