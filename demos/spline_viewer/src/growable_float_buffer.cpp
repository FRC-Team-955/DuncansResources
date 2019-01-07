#include <growable_float_buffer.hpp>

GrowableFloatBuffer::GrowableFloatBuffer() {
    // Create a new vertex array
    glGenVertexArrays(1, &array_id);

    // We're going to talk about this array
    glBindVertexArray(array_id);

    // Create the new buffer
    create_buffer();
}

// Simple accessor
GLuint GrowableFloatBuffer::get_handle() { return buffer_handle; }

size_t GrowableFloatBuffer::local_capacity_bytes() {
    // Capacity is listed in # of elements, calculate actual # of bytes
    return local_buffer.capacity() * sizeof(GLfloat);
}

size_t GrowableFloatBuffer::local_used_bytes() {
    // # used is listed in # of elements, calculate actual # of bytes
    return local_buffer.size() * sizeof(GLfloat);
}

void GrowableFloatBuffer::create_buffer() {
    // Create a new buffer
    glGenBuffers(1, &buffer_handle);

    // We're going to talk about this buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);

    // Allocate, but do not populate the new buffer, with buffer_capacity size.
    glBufferData(GL_ARRAY_BUFFER, buffer_capacity, nullptr, GL_DYNAMIC_DRAW);
}

void GrowableFloatBuffer::commit() {
    // Check whether or not the local buffer will fit into allocated graphics memory
    if (local_used_bytes() > buffer_capacity) {
        // Free the old buffer on the graphics card
        glDeleteBuffers(1, &buffer_handle);

        // Set the new desired buffer capacity
        buffer_capacity = local_capacity_bytes();

        // Create a new buffer with appropriate size to accomodate the new data
        create_buffer();
    }

    // We're going to talk about this buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);

    // Actually upload the new buffer data to the GPU
    printf("SUB DATA %lu\n", local_used_bytes());
    glBufferSubData(GL_ARRAY_BUFFER, 0, local_used_bytes(), &local_buffer.front());
}

GrowableFloatBuffer::~GrowableFloatBuffer() {
    // Free the buffer when deconstructing
    glDeleteBuffers(1, &buffer_handle);
}
