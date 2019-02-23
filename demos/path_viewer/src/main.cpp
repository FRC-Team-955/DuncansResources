#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <motion_state.hpp>
#include <primitive_renderer.hpp>
#include <spline.hpp>
#include <spline_parametric.hpp>
#include <tank_drive.hpp>
#include <vec2.hpp>
#include <vector>

// Forward declare the boilerplate function (defined futher down)
GLFWwindow* boilerplate();

int main() {
    // Set up OpenGL
    GLFWwindow* window = boilerplate();

    // Set the screen view (Left, Right, Bottom, Top)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Robot settings
    const float max_velocity = 0.5;
    const float time_interval = 0.02;
    const float wheel_distance = 0.1;

    // Control points
    TinyVec::Vec2 a(0.0, 0.0);
    TinyVec::Vec2 b(0.9, -0.6);
    TinyVec::Vec2 c(-0.8, 0.6);
    TinyVec::Vec2 d(-0.6, -0.7);

    // Point renderer object, manages rendering of points
    PrimitiveRenderer points(GL_POINTS);
    glPointSize(5);  // Set the OpenGL points size to something we can see

    // Line renderer, manages rendering of lines_center
    PrimitiveRenderer lines_center(GL_LINES);
    PrimitiveRenderer lines_left(GL_LINES);
    PrimitiveRenderer lines_right(GL_LINES);
    glLineWidth(2);  // Sane line width

    // Animation variable
    float increment = 0.0;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Animate one of the control points to move in a circle
        increment += 0.01;
        b.x = cos(increment);
        b.y = sin(increment);

        points.clear();  // Clear previous entries
        // Add all of the control points to the current buffer
        points.push(GraphicPoint{a, 1.0, 1.0, 1.0});
        points.push(GraphicPoint{b, 1.0, 1.0, 1.0});
        points.push(GraphicPoint{c, 1.0, 1.0, 1.0});
        points.push(GraphicPoint{d, 1.0, 1.0, 1.0});
        points.commit();  // Push new entries to the GPU

        // Clear the line buffers
        lines_center.clear();
        lines_left.clear();
        lines_right.clear();

        // Store the last line vertex so it can start the next line
        TinyVec::Vec2 last_center;
        TinyVec::Vec2 last_left;
        TinyVec::Vec2 last_right;

        // Iterate over the spline
        float index = 0.0;
        while (index < 1.0) {
            // Calculate vertex position for the spline
            MotionState parametric = spline_parametric(a, b, c, d, index);
            TankDrive::TankOutput output;
            TankDrive::evaluate(parametric, output, max_velocity, time_interval,
                    wheel_distance);
            index += output.change_in_index;

            // Add the line vertices
            lines_center.push(GraphicLine{
                    GraphicPoint{parametric.position, 1.0, 1.0, 1.0},
                    GraphicPoint{last_center, 1.0, 1.0, 1.0},
                    });

            // Coloring
            float left_velocity_frac =
                fabs(output.left_wheel_velocity / max_velocity);
            float right_velocity_frac =
                fabs(output.right_wheel_velocity / max_velocity);
            float r_left =
                output.left_wheel_velocity < 0.0 ? left_velocity_frac : 0.0;
            float r_right =
                output.right_wheel_velocity < 0.0 ? right_velocity_frac : 0.0;
            float g_left =
                output.left_wheel_velocity < 0.0 ? 0.0 : left_velocity_frac;
            float g_right =
                output.right_wheel_velocity < 0.0 ? 0.0 : right_velocity_frac;

            lines_left.push(GraphicLine{
                    GraphicPoint{output.left_wheel_position, r_left, g_left, 0.0},
                    GraphicPoint{last_left, r_left, g_left, 0.0},
                    });

            lines_right.push(GraphicLine{
                    GraphicPoint{output.right_wheel_position, r_right, g_right, 0.0},
                    GraphicPoint{last_right, r_right, g_right, 0.0},
                    });

            // Remember where we were this time so we can start there on the next
            last_center = parametric.position;
            last_left = output.left_wheel_position;
            last_right = output.right_wheel_position;
        }
        // Commit changes to the GPU
        lines_center.commit();
        lines_left.commit();
        lines_right.commit();

        // Actually draw the contents of the renderers
        lines_center.draw();
        lines_left.draw();
        lines_right.draw();
        points.draw();

        // Show what we rendered on screen
        glfwSwapBuffers(window);

        // Poll
        glfwPollEvents();
    }

    // Free the window
    glfwDestroyWindow(window);
}

// GLFW error callback (function). Prints messages from GLFW
void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

// Called when the window resizes, maintains the aspect ratio
void glfw_window_resize_callback(GLFWwindow* window, int width, int height) {
    int min = std::min(width, height);
    glViewport(0, 0, (GLsizei)min, (GLsizei)min);
}

// Set up OpenGL, etc.
GLFWwindow* boilerplate() {
    // Try to initialize GLFW
    if (!glfwInit()) {
        // Initialization failed. Message and shut down.
        fprintf(stderr, "GLFW Failed to initialize.\n");
        exit(EXIT_FAILURE);
    }

    // Set an error message callback for GLFW
    glfwSetErrorCallback(glfw_error_callback);

    // Set up window parameters
    glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
            GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

    // Create a window for OpenGL to draw upon
    GLFWwindow* window = glfwCreateWindow(640, 480, "Spline viewer", NULL, NULL);
    if (!window) {
        // Window or OpenGL context creation failed
        fprintf(stderr, "GLFW Failed to create a window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Set the OpenGL context to the window
    glfwMakeContextCurrent(window);

    // Set the window resize callback function
    glfwSetWindowSizeCallback(window, glfw_window_resize_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    return window;
}
