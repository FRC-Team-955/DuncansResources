#include <primitive_renderer.hpp>

PrimitiveRenderer::PrimitiveRenderer(GLenum draw_type) : draw_type(draw_type) {
    shader_program = load_shaders((char *)"../shaders/vertex.glsl",
            (char *)"../shaders/fragment.glsl");
}

void PrimitiveRenderer::push(GraphicPoint point) {
    vertices.local_buffer.push_back(point.position.x);
    vertices.local_buffer.push_back(point.position.y);
    colors.local_buffer.push_back(point.r);
    colors.local_buffer.push_back(point.g);
    colors.local_buffer.push_back(point.b);
    elements_stored++;
}

void PrimitiveRenderer::push(GraphicLine line) {
    push(line.start);
    push(line.end);
}

void PrimitiveRenderer::draw() {
    glUseProgram(shader_program);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertices.get_handle());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, colors.get_handle());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(draw_type, 0, elements_stored);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void PrimitiveRenderer::clear() {
    elements_stored = 0;
    vertices.local_buffer.clear();
    colors.local_buffer.clear();
}

void PrimitiveRenderer::commit() {
    vertices.commit();
    colors.commit();
}

PrimitiveRenderer::~PrimitiveRenderer() { glDeleteShader(shader_program); }
