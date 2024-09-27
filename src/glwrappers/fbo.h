#pragma once

#include "GL/glew.h"

#include <vector>
#include "texture.h"
#include "rbo.h"

class FBO
{
    // This is needed because of a QT peculiarity:
    // The default fbo is the last fbo ID allocated + 1
    // This alone here makes FBO class NOT thread-safe
    static GLuint __default_fbo;

public:
    FBO();
    ~FBO();

    void initialize(int w, int h);
    void initializeGBuffer(int w, int h);

    void bindFBO();
    void unbindFBO();
    void bindTexture();
    void bindAllTextures();
    void unbindAllTextures();
    void unbindTexture();
    void bindRenderbuffer();
    void unbindRenderbuffer();

private:
    GLuint m_handle;
    std::vector<Texture> m_textures;
    RBO m_renderbuffer;
    int m_width;
    int m_height;
};
