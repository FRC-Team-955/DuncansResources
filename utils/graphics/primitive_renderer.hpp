#pragma once
#include <GL/glew.h>
#include <growable_float_buffer.hpp>
#include <load_shader.hpp>
#include <vec2.hpp>
#include <vector>

struct GraphicPoint {
    TinyVec::Vec2 position;
    float r, g, b;
};

struct GraphicLine {
    GraphicPoint start;
    GraphicPoint end;
};

class PrimitiveRenderer {
    public:
        PrimitiveRenderer(GLenum draw_type);
        void clear();
        void push(GraphicLine line);
        void push(GraphicPoint point);
        void commit();
        void draw();
        ~PrimitiveRenderer();

    private:
        GLenum draw_type;
        size_t elements_stored = 0;
        size_t count_elements();
        GLuint shader_program;
        GrowableFloatBuffer vertices;
        GrowableFloatBuffer colors;
};
