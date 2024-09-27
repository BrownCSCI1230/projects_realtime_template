Latest findings:
In QT, you're not allowed to do any GL calls before initializeGL, so my RAII scheme is moot
The way I would be able to get around it is by... INDIRECTION!
This class is the answer. And realtime.h needs to hold a unique_ptr to an instance of this class

#pragma once

// Defined before including GLEW to suppress deprecation messages on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>

#include "glwrappers/fbo.h"
#include "glwrappers/vao.h"
#include "glwrappers/vbo.h"
#include "glwrappers/shader.h"
#include "glwrappers/glinitializer.h"

class GLRealtime
{
public:
    GlRealtime();
    ~GlRealtime();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();
    void saveViewportImage(std::string filePath);

    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

    void initializeGL();                       // Called once at the start of the program
    void paintGL();                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height);      // Called when window size changes

private:
    // void keyPressEvent(QKeyEvent *event);
    // void keyReleaseEvent(QKeyEvent *event);
    // void mousePressEvent(QMouseEvent *event);
    // void mouseReleaseEvent(QMouseEvent *event);
    // void mouseMoveEvent(QMouseEvent *event);
    // void timerEvent(QTimerEvent *event);

    // Tick Related Variables
    int m_timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer m_elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    // Input Related Variables
    bool m_mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 m_prev_mouse_pos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    double m_devicePixelRatio;

    int32_t m_screen_width;
    int32_t m_screen_height;


    VBO m_quad_vbo;
    VAO m_quad_vao;

    Shader m_phong_shader;

    void createFullScreenQuad();
    void createShaders();

};


#endif // GL-REALTIME_H
