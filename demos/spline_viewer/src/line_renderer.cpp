#include <line_renderer.hpp>

void LineRenderer::push(GraphicLine line) {
    vertices.local_buffer.push_back(line.start.x);
    vertices.local_buffer.push_back(line.start.y);
    colors.local_buffer.push_back(line.r);
    colors.local_buffer.push_back(line.g);
    colors.local_buffer.push_back(line.b);
    elements_stored++;

    vertices.local_buffer.push_back(line.end.x);
    vertices.local_buffer.push_back(line.end.y);
    colors.local_buffer.push_back(line.r);
    colors.local_buffer.push_back(line.g);
    colors.local_buffer.push_back(line.b);
    elements_stored++;
}

LineRenderer::LineRenderer() {
    shader_program = load_shaders((char *)"../shaders/vertex.glsl",
            (char *)"../shaders/fragment.glsl");
}

void LineRenderer::draw() {
    glUseProgram(shader_program);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertices.get_handle());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, colors.get_handle());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_LINES, 0, elements_stored);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void LineRenderer::clear() {
    elements_stored = 0;
    vertices.local_buffer.clear();
    colors.local_buffer.clear();
}

void LineRenderer::commit() {
    vertices.commit();
    colors.commit();
}

LineRenderer::~LineRenderer() { glDeleteShader(shader_program); }
