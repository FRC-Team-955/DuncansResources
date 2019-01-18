#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <load_shader.hpp>

using namespace glm;

// GLFW error callback (function). Prints messages from GLFW
void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main() {
    // Boilerplate setup for the window and such

    // Try to initialize GLFW
    if (!glfwInit()) {
        // Initialization failed. Message and shut down.
        fprintf(stderr, "GLFW Failed to initialize.\n");
        return EXIT_FAILURE;
    }

    // Set an error message callback for GLFW
    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Create a window for OpenGL to draw upon
    GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window) {
        // Window or OpenGL context creation failed
        fprintf(stderr, "GLFW Failed to create a window.\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Set the OpenGL context to the window
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return EXIT_FAILURE;
    }

    // OpenGL setup
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, //
        1.0f, -1.0f, 0.0f, //
        0.0f, 1.0f, 0.0f, //
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
            g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint program = load_shaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 1st attribute buffer : vertices
        glUseProgram(program);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but
                // must match the layout in the shader.
                3, // size
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0,        // stride
                (void *)0 // array buffer offset
                );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0,
                3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free the window
    glfwDestroyWindow(window);
}
