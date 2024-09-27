#pragma once

#include "GL/glew.h"
#include <vector>

class VBO
{
public:
    VBO();
    ~VBO();

    void setData(std::vector<float> data);
    void bind();
    void unbind();
    GLsizei getLength();

private:
    GLuint m_handle;
    GLsizei m_length;
};
