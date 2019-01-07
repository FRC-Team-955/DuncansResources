#include <parametric_output.hpp>
#include <spline.hpp>
#include <spline_parametric.hpp>
#include <stdio.h>
#include <tank_drive.hpp>
#include <vec2.hpp>

int main()
{
    float index = 0.0;

    TinyVec::Vec2 a(0.0, 0.0);
    TinyVec::Vec2 b(0.9, -0.6);
    TinyVec::Vec2 c(-0.8, 0.6);
    TinyVec::Vec2 d(-0.6, -0.7);

    while (index < 1.0) {
        ParametricOutput parametric = spline_parametric(a, b, c, d, index);
        TankDrive::TankOutput output;
        index += TankDrive::evaluate(parametric, output, 0.5, 0.05, 0.02);
        printf("%f: %4f %4f\n",
                index,
                output.motion.velocity_left,
                output.motion.velocity_right);
    }
}
