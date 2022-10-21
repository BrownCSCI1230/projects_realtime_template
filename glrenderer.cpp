#include "glrenderer.h"

#include <QCoreApplication>
#include "settings.h"

GLRenderer::GLRenderer(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_prev_mouse_pos = glm::vec2(size().width()/2, size().height()/2);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    // Set up key mappings
    m_keyMap[Qt::Key_W] = false;
    m_keyMap[Qt::Key_A] = false;
    m_keyMap[Qt::Key_S] = false;
    m_keyMap[Qt::Key_D] = false;
    m_keyMap[Qt::Key_Control] = false;
    m_keyMap[Qt::Key_Space] = false;
}

void GLRenderer::finish(){
    killTimer(m_timer);

    makeCurrent();

    // Anything requiring OpenGL calls when the program exits should be done in here

    doneCurrent();
}

void GLRenderer::initializeGL(){
    m_devicePixelRatio = this->devicePixelRatio();

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));

    m_timer = startTimer(1000/60);
    m_elapsedTimer.start();
}

void GLRenderer::paintGL(){
    
}

void GLRenderer::resizeGL(int w, int h){
    update(); // Asks for a PaintGL call to occur
}

void GLRenderer::settingsChange(){
    update(); // Asks for a PaintGL call to occur
}

void GLRenderer::keyPressEvent(QKeyEvent *event){
    m_keyMap[Qt::Key(event->key())] = true;
}

void GLRenderer::keyReleaseEvent(QKeyEvent *event){
    m_keyMap[Qt::Key(event->key())] = false;
}

void GLRenderer::mousePressEvent(QMouseEvent *event){
    if(event->buttons().testFlag(Qt::LeftButton)){
        m_mouseDown = true;
        m_prev_mouse_pos = glm::vec2(event->position().x(), event->position().y());
    }
}

void GLRenderer::mouseReleaseEvent(QMouseEvent *event){
    if(!event->buttons().testFlag(Qt::LeftButton)){
        m_mouseDown = false;
    }
}

void GLRenderer::mouseMoveEvent(QMouseEvent *event){
    if(m_mouseDown){
        int posX = event->position().x();
        int posY = event->position().y();
        int deltaX = posX - m_prev_mouse_pos.x;
        int deltaY = posY - m_prev_mouse_pos.y;
        m_prev_mouse_pos = glm::vec2(posX, posY);
	// Use deltaX and deltaY here to rotate

        update(); // Asks for a PaintGL call to occur
    }
}

void GLRenderer::timerEvent(QTimerEvent *event){
    elapsedms = m_elapsedTimer.elapsed();
    deltaTime = elapsedms*0.001f;
    update(); // Asks for a PaintGL call to occur
}