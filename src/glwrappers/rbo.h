#pragma once

#include "GL/glew.h"

class RBO
{
public:
    RBO();
    ~RBO();

    GLuint initialize(int w, int h);

    void bind();
    void unbind();
    GLuint getHandle();

private:
    GLuint m_handle;
};
