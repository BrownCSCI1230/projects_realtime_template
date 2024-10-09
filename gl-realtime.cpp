#include "gl-realtime.h"
#include "utils/shaderloader.h"

#include <GL/glew.h>
#include <iostream>

GlRealtime::GlRealtime(size_t width, size_t height, double device_pixel_ratio) :
    m_gl_initializer(),
    m_devicePixelRatio(device_pixel_ratio),
    m_screen_width(int32_t(width * device_pixel_ratio)),
    m_screen_height(int32_t(height * device_pixel_ratio))
{
    // Allows OpenGL to draw objects appropriately on top of one another
    glEnable(GL_DEPTH_TEST);
    // Tells OpenGL to only draw the front face
    glEnable(GL_CULL_FACE);
    // Tells OpenGL how big the screen is
    glViewport(0, 0, m_screen_width, m_screen_height);

    // Students: anything requiring OpenGL calls when the program starts should be done here

    createFullScreenQuad();
    createShaders();
}

GlRealtime::~GlRealtime() {}


void GlRealtime::resize(size_t width, size_t height) {
    // TODO
}

void GlRealtime::createFullScreenQuad() {
    static const std::vector<GLfloat> fullscreen_quad_data =
        {   // x, y, z, u, v    //
            -1.0f,  1.0f, 0.0f,
            0.0f,  1.0f,
            -1.0f, -1.0f, 0.0f,
            0.0f,  0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  0.0f,
            1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,
            -1.0f,  1.0f, 0.0f,
            0.0f,  1.0f
        };

    m_quad_vbo.setData(fullscreen_quad_data);
    m_quad_vao.setData(m_quad_vbo, VAOAttrib::POS | VAOAttrib::UV);
}

void GlRealtime::createShaders() {
    GLuint default_shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");
    m_phong_shader.initialize(default_shader);
}

void GlRealtime::paint() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phong_shader.bind();
    m_quad_vao.draw();
    m_phong_shader.unbind();
}
