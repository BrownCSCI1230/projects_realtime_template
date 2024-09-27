#include "rbo.h"
#include "utils/debug.h"

RBO::RBO() {
    glGenRenderbuffers(1, &m_handle);
    glErrorCheck();
}

RBO::~RBO() {
    glDeleteRenderbuffers(1, &m_handle);
    glErrorCheck();
}

GLuint RBO::initialize(int w, int h){
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    unbind();

    glErrorCheck();
    return m_handle;
}

void RBO::bind(){
    glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

void RBO::unbind(){
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLuint RBO::getHandle(){
    return m_handle;
}
