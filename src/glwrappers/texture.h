#pragma once

#include "GL/glew.h"

class Texture
{
public:
    Texture();
    ~Texture();

    GLuint initialize(int w, int h, GLenum slot = GL_TEXTURE0, GLenum internalFormat = GL_RGBA, GLenum dataType = GL_UNSIGNED_BYTE, GLenum filterMode = GL_LINEAR);

    void bind(GLenum slot = GL_TEXTURE0);
    void unbind(GLenum slot = GL_TEXTURE0);
    GLuint getHandle();
    GLuint getTexUnit();

private:
    GLuint m_handle;
};
