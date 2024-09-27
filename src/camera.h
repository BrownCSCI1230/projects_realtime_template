#pragma once

#include "utils/sceneparser.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Camera
{
public:
    void setData(RenderData data, int w, int h);
    void finish();

    glm::mat4 getProjection();
    glm::mat4 getView();
    glm::mat4 getInverseProjection();
    glm::mat4 getInverseView();
    glm::vec3 getWorldSpacePos();
    void resize(float new_w, float new_h);
    float getNear();
    float getFar();
    void setClipping(float near, float far);
    void translate(glm::vec3 direction);
    void rotate(float vertical, float horizontal);

private:
    glm::mat4 lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    glm::mat4 perspective(float fov, float aspect, float near, float far);

    float m_near;
    float m_far;
    float m_aspect;
    float m_fov;
    float m_widthAngle;

    glm::vec3 m_pos;
    glm::vec3 m_look;
    glm::vec3 m_up;

    glm::mat4 m_proj = glm::mat4(1);
    glm::mat4 m_view = glm::mat4(1);
    glm::mat4 m_invProj = glm::mat4(1);
    glm::mat4 m_invView = glm::mat4(1);
};
