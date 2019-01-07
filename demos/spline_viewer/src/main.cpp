#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vec2.hpp>
#include <vector>
#include <line_renderer.hpp>
#include <spline.hpp>

//using namespace glm;

// GLFW error callback (function). Prints messages from GLFW
void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void glfw_window_resize_callback(GLFWwindow* window, int width, int height) {
    int min = std::min(width, height);
    glViewport(0, 0, (GLsizei)min, (GLsizei)min);
}

float random_uniform_float() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float random_bi_float() {
    return 2.0 * random_uniform_float() - 1.0;
}

GLFWwindow* boilerplate();

int main() {
    GLFWwindow* window = boilerplate();

    TinyVec::Vec2 a(0.0, 0.0);
    TinyVec::Vec2 b(0.9, -0.6);
    TinyVec::Vec2 c(-0.8, 0.6);
    TinyVec::Vec2 d(-0.6, -0.7);

    LineRenderer lines;

    // Main loop
    float increment = 0.0;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLineWidth(3);
        
        increment += 0.01;
        b.x = cos(increment);
        b.y = sin(increment);

        lines.clear();
        TinyVec::Vec2 last;
        for (float i = 0.0; i < 1.0; i += 0.01) {
            TinyVec::Vec2 current = spline(a, b, c, d, i); 
            lines.push({ last, current, i, 1.0f - i, i });
            last = current;
        }
        lines.commit();

        lines.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free the window
    glfwDestroyWindow(window);
}

GLFWwindow* boilerplate() {
    // Try to initialize GLFW
    if (!glfwInit()) {
        // Initialization failed. Message and shut down.
        fprintf(stderr, "GLFW Failed to initialize.\n");
        exit(EXIT_FAILURE);
    }

    // Set an error message callback for GLFW
    glfwSetErrorCallback(glfw_error_callback);

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

    glfwSetWindowSizeCallback(window, glfw_window_resize_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }

    return window;
}
