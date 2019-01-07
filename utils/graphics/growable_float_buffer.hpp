#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <vector>

class GrowableFloatBuffer {
    public:
        // Construct a new buffer
        GrowableFloatBuffer();

        // Buffer local to the CPU
        std::vector<GLfloat> local_buffer;

        // Commit the local buffer into graphics memory
        void commit();

        // Safely get the handle for the GPU memory
        GLuint get_handle();

        // Deconstruct the buffer safely
        ~GrowableFloatBuffer();

    private:
        // GPU buffer handle
        GLuint buffer_handle;

        // GPU buffer array id
        GLuint array_id;

        // Current GPU buffer capacity
        size_t buffer_capacity = 64;

        // Calculate capacity for CPU local buffer in bytes
        size_t local_capacity_bytes();
        
        // Calculate used elements for CPU local buffer in bytes
        size_t local_used_bytes();

        // Create a new buffer with capacity equal to buffer_capacity
        void create_buffer();
};
