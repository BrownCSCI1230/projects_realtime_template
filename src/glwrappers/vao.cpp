#include "vao.h"
#include "utils/debug.h"

VAO::VAO() {
    glGenVertexArrays(1, &m_handle);
    glErrorCheck();
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &m_handle);
    glErrorCheck();
}

void VAO::reset() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void VAO::setData(VBO &vbo, VAOAttrib attribs) {
    reset();

    m_attribs = attribs;
    m_vbo = &vbo;
    m_curr_offset = 0;
    m_vert_size = 0;

    bind();

    m_vert_size = getVertexSize();

    setAttributes();

    unbind();
}

GLuint VAO::getVertexSize() {
    GLuint size = 0;
    if(m_attribs & VAOAttrib::POS){
        size += 3;
    }
    if(m_attribs & VAOAttrib::NORM){
        size += 3;
    }
    if(m_attribs & VAOAttrib::UV){
        size += 2;
    }
    return size;
}

void VAO::bind() {
    glBindVertexArray(m_handle);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::setAttributes() {
    m_vbo->bind();

    if(m_attribs & VAOAttrib::POS){
        addAttribute(0, 3);
    }
    if(m_attribs & VAOAttrib::NORM){
        addAttribute(1, 3);
    }
    if(m_attribs & VAOAttrib::UV){
        addAttribute(2, 2);
    }

    m_vbo->unbind();
}

void VAO::addAttribute(GLuint attrib_index, GLint attrib_size) {
    glEnableVertexAttribArray(attrib_index);
    glVertexAttribPointer(attrib_index, attrib_size, GL_FLOAT, GL_FALSE, m_vert_size*sizeof(GLfloat), reinterpret_cast<void*>(m_curr_offset*sizeof(GLfloat)));
    m_curr_offset += attrib_size;
}

void VAO::draw(){
    bind();
    glDrawArrays(GL_TRIANGLES, 0, m_vbo->getLength()/m_vert_size);
    unbind();
}

void VAO::debug() {
    std::cout<<m_vbo->getLength()<<std::endl;
    std::cout<<m_vert_size<<std::endl;
}
