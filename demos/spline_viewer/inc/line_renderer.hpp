#pragma once
#include <GL/glew.h>
#include <growable_float_buffer.hpp>
#include <load_shader.hpp>
#include <vec2.hpp>
#include <vector>

struct GraphicLine {
    TinyVec::Vec2 start;
    TinyVec::Vec2 end;
    float r, g, b;
};

class LineRenderer {
    public:
        LineRenderer();
        void clear();
        void push(GraphicLine line);
        void commit();
        void draw();
        ~LineRenderer();

    private:
        size_t elements_stored = 0;
        size_t count_elements();
        GLuint shader_program;
        GrowableFloatBuffer vertices;
        GrowableFloatBuffer colors;
};
