#pragma once

#include "vbo.h"

enum class VAOAttrib{
    POS = 1,
    NORM = 2,
    UV = 4
};

inline VAOAttrib operator|(VAOAttrib lhs, VAOAttrib rhs){
    using VAOAttribType = std::underlying_type<VAOAttrib>::type;
    return VAOAttrib(static_cast<VAOAttribType>(lhs) | static_cast<VAOAttribType>(rhs));
}

inline bool operator&(VAOAttrib lhs, VAOAttrib rhs){
    using VAOAttribType = std::underlying_type<VAOAttrib>::type;
    return static_cast<bool>(VAOAttrib(static_cast<VAOAttribType>(lhs) & static_cast<VAOAttribType>(rhs)));
}

class VAO
{
public:
    VAO();
    ~VAO();

    void setData(VBO& vbo, VAOAttrib attribs);
    void bind();
    void unbind();
    void draw();
    void debug();

private:
    void reset();
    GLuint getVertexSize();
    void setAttributes();
    void addAttribute(GLuint attrib_index, GLint attrib_size);

    VBO* m_vbo = nullptr;
    VAOAttrib m_attribs;
    GLuint m_handle;
    GLint m_curr_offset;
    GLuint m_vert_size;
};
