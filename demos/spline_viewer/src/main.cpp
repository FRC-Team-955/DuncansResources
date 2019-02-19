#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <vec2.hpp>
#include <vector>
#include <primitive_renderer.hpp>
#include <spline.hpp>

// Forward declare the boilerplate function (defined futher down)
GLFWwindow* boilerplate();

int main() {
    // Set up OpenGL
    GLFWwindow* window = boilerplate();

    // Set the screen view (Left, Right, Bottom, Top)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Control points
    TinyVec::Vec2 a(0.0, 0.0);
    TinyVec::Vec2 b(0.9, -0.6);
    TinyVec::Vec2 c(-0.8, 0.6);
    TinyVec::Vec2 d(-0.6, -0.7);

    // Point renderer object, manages rendering of points
    PrimitiveRenderer points(GL_POINTS);
    glPointSize(5); // Set the OpenGL points size to something we can see

    // Line renderer, manages rendering of lines
    PrimitiveRenderer lines(GL_LINES);
    glLineWidth(2); // Sane line width

    // Animation variable
    float increment = 0.0;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Animate one of the control points to move in a circle
        increment += 0.01;
        b.x = cos(increment);
        b.y = sin(increment);

        points.clear(); // Clear previous entries
        // Add all of the control points to the current buffer
        points.push(GraphicPoint { a, 1.0, 1.0, 1.0 });
        points.push(GraphicPoint { b, 1.0, 1.0, 1.0 });
        points.push(GraphicPoint { c, 1.0, 1.0, 1.0 });
        points.push(GraphicPoint { d, 1.0, 1.0, 1.0 });
        points.commit(); // Push new entries to the GPU

        lines.clear(); // Clear the line buffer

        // Store the last line vertex so it can start the next line
        TinyVec::Vec2 last; 

        // Iterate over the spline
        for (float i = 0.0; i < 1.0; i += 0.01) {
            // Calculate vertex position for the spline
            TinyVec::Vec2 current = spline(a, b, c, d, i); 

            // Add the line vertices
            lines.push(
                GraphicLine { 
                    // Position, color.r, color.g, color.b
                     GraphicPoint {current, i, 1.0f - i, i}, 
                     GraphicPoint {last, i, 1.0f - i, i}, 
                 });

            // Remember where we were this time so we can start there on the next
            last = current;
        }
        // Commit changes to the GPU
        lines.commit();

        // Actually draw the contents of the renderers
        lines.draw();
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
void glfw_error_callback(int error, const char *description) {
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
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Create a window for OpenGL to draw upon
    GLFWwindow *window = glfwCreateWindow(640, 480, "Spline viewer", NULL, NULL);
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
