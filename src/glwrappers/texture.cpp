#include "texture.h"
#include "utils/debug.h"

Texture::Texture() {
    glGenTextures(1, &m_handle);
    glErrorCheck();
}

Texture::~Texture() {
    glDeleteTextures(1, &m_handle);
    glErrorCheck();
}

GLuint Texture::initialize(int w, int h, GLenum slot, GLenum internalFormat, GLenum dataType, GLenum filterMode) {
    bind(slot);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, GL_RGBA, dataType, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
    unbind(slot);

    glErrorCheck();
    return m_handle;
}

void Texture::bind(GLenum slot) {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::unbind(GLenum slot) {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getHandle() {
    return m_handle;
}
