#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <glwrappers/glinitializer.h>
#include "glwrappers/fbo.h"
#include "glwrappers/vao.h"
#include "glwrappers/vbo.h"
#include "glwrappers/shader.h"

#include "utils/scenefilereader.h"
#include "camera.h"
#include "settings.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>
#include <unordered_map>

class GlRealtime
{
    GLInitializer m_gl_initializer;
public:
    GlRealtime(size_t width, size_t height, double device_pixel_ratio);
    ~GlRealtime();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();

    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

    void paint();                            // Called whenever the OpenGL context changes or by an update() request
    void resize(size_t width, size_t height);      // Called when window size changes

    void loadScene(const std::string& filepath, int near, int far);

private:
    GlRealtime();                        // Disallow default constructor
    GlRealtime(const GlRealtime& other); // Disallow copy constructor

    // Device Correction Variables
    double m_devicePixelRatio;

    RenderData m_render_data;
    Camera m_camera;

    int32_t m_screen_width;
    int32_t m_screen_height;

    VBO m_quad_vbo;
    VAO m_quad_vao;

    std::unordered_map<PrimitiveType, VBO> m_shapeVBOs;
    std::unordered_map<PrimitiveType, VAO> m_shapeVAOs;

    int32_t m_tesselation_param1;
    int32_t m_tesselation_param2;

    Shader m_phong_shader;

    void createFullScreenQuad();
    void createShaders();
    //void initVBuffers();
    void updateShapes();

};
