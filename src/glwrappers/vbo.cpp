#include "vbo.h"
#include "utils/debug.h"

VBO::VBO() {
    glGenBuffers(1, &m_handle);
    glErrorCheck();
}

VBO::~VBO() {
    glDeleteBuffers(1, &m_handle);
    glErrorCheck();
}

void VBO::setData(std::vector<float> data) {
    m_length = data.size();
    bind();
    glBufferData(GL_ARRAY_BUFFER, m_length*sizeof(float), data.data(), GL_STATIC_DRAW);
    unbind();
    glErrorCheck();
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLsizei VBO::getLength() {
    return m_length;
}
