#include "fbo.h"
#include "utils/debug.h"

GLuint FBO::__default_fbo = 1;

FBO::FBO() {
    glGenFramebuffers(1, &m_handle);
    glErrorCheck();
    FBO::__default_fbo = m_handle + 1;
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &m_handle);
    glErrorCheck();
}

void FBO::initialize(int w, int h)
{
    m_width = w;
    m_height = h;

    m_textures.push_back(Texture());
    m_textures[0].initialize(w, h);
    m_renderbuffer.initialize(w, h);

    bindFBO();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures[0].getHandle(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer.getHandle());
    unbindFBO();

    glErrorCheck();
}

void FBO::initializeGBuffer(int w, int h)
{
    glGenFramebuffers(1, &m_handle);
    bindFBO();

    // Position
    m_textures.push_back(Texture());
    m_textures[0].initialize(w, h, GL_TEXTURE0, GL_RGBA16F, GL_FLOAT, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures[0].getHandle(), 0);
    // Normals
    m_textures.push_back(Texture());
    m_textures[1].initialize(w, h, GL_TEXTURE1, GL_RGBA16F, GL_FLOAT, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textures[1].getHandle(), 0);
    // Ambient Color
    m_textures.push_back(Texture());
    m_textures[2].initialize(w, h, GL_TEXTURE2, GL_RGBA16F, GL_UNSIGNED_BYTE, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_textures[2].getHandle(), 0);
    // Diffuse Color
    m_textures.push_back(Texture());
    m_textures[3].initialize(w, h, GL_TEXTURE3, GL_RGBA16F, GL_UNSIGNED_BYTE, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_textures[3].getHandle(), 0);
    // Specular Color
    m_textures.push_back(Texture());
    m_textures[4].initialize(w, h, GL_TEXTURE4, GL_RGBA16F, GL_UNSIGNED_BYTE, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_textures[4].getHandle(), 0);
    m_renderbuffer.initialize(w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer.getHandle());
    unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4};
    glDrawBuffers(5, attachments);
    unbindFBO();

    glErrorCheck();

}

void FBO::bindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
}

void FBO::unbindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO::__default_fbo);
}

void FBO::bindTexture()
{
    m_textures[0].bind();
}

void FBO::bindAllTextures()
{
    m_textures[0].bind(GL_TEXTURE0);
    m_textures[1].bind(GL_TEXTURE1);
    m_textures[2].bind(GL_TEXTURE2);
    m_textures[3].bind(GL_TEXTURE3);
    m_textures[4].bind(GL_TEXTURE4);
}

void FBO::unbindTexture()
{
    m_textures[0].unbind();
}

void FBO::unbindAllTextures()
{
    m_textures[0].unbind(GL_TEXTURE0);
    m_textures[1].unbind(GL_TEXTURE1);
    m_textures[2].unbind(GL_TEXTURE2);
    m_textures[3].unbind(GL_TEXTURE3);
    m_textures[4].unbind(GL_TEXTURE4);
}

void FBO::bindRenderbuffer()
{
    m_renderbuffer.bind();
}

void FBO::unbindRenderbuffer()
{
    m_renderbuffer.unbind();
}
