#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "GL/glew.h"
#include <QOpenGLWidget>
#include "glm/glm.hpp"
#include <unordered_map>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>

class GLRenderer : public QOpenGLWidget
{
public:
    GLRenderer(QWidget *parent = nullptr);
    void finish();
    void settingsChange();

public slots:
    void tick();

protected:
    void initializeGL() override;   //Called once at the start of the program
    void paintGL() override;    //Called every frame in a loop
    void resizeGL(int width, int height) override;  //Called when window size changes

private:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    //Tick Related Variables
    int m_timer;
    QElapsedTimer m_elapsedTimer;

    //Input Related Variables
    bool m_mouseDown = false;
    glm::vec2 m_prev_mouse_pos; //Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;

    //Device Correction Variables
    int m_devicePixelRatio;
};

#endif // GLRENDERER_H
