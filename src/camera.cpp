#include "camera.h"

void Camera::init(
    RenderData data,
    int w,
    int h,
    int near,
    int far
) {
    m_near = near;
    m_far = far;
    m_fov = data.cameraData.heightAngle;
    m_pos = glm::vec3(data.cameraData.pos);
    m_look = glm::vec3(data.cameraData.look);
    m_up = glm::vec3(data.cameraData.up);
    m_aspect = w/float(h);
    m_widthAngle = 2*glm::atan(m_aspect*glm::tan(m_fov/2.f));

    recomputeView();
    recomputeProjection();
}

void Camera::recomputeView() {
    m_view = lookAt(m_pos, m_pos + m_look, m_up);
    m_invView = glm::inverse(m_view);
}

void Camera::recomputeProjection() {
    m_proj = perspective(m_fov, m_aspect, m_near, m_far);
    m_invProj = glm::inverse(m_proj);
}

void Camera::finish() {

}

glm::mat4 Camera::getProjection() {
    return m_proj;
}

glm::mat4 Camera::getView() {
    return m_view;
}

glm::mat4 Camera::getInverseProjection() {
    return m_invProj;
}

glm::mat4 Camera::getInverseView() {
    return m_invView;
}

glm::vec3 Camera::getWorldSpacePos(){
    return m_pos;
}

void Camera::resize(float new_w, float new_h){
    m_aspect = new_w/new_h;
    recomputeProjection();
}

glm::mat4 Camera::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    return glm::lookAt(eye, center, up); // TODO: Replace
}

glm::mat4 Camera::perspective(float fov, float aspect, float near, float far) {
    glm::mat4 mat1 = glm::mat4(
        glm::vec4(1.f/(far*aspect*glm::tan(m_fov/2.f)), 0, 0, 0),
        glm::vec4(0, 1.f/(glm::tan(m_fov/2.f)*far), 0, 0),
        glm::vec4(0, 0, 1.f/far, 0),
        glm::vec4(0, 0, 0, 1)
    );

    float c = -near/far;
    glm::mat4 mat2 = glm::mat4(
        glm::vec4(1, 0, 0, 0),
        glm::vec4(0, 1, 0, 0),
        glm::vec4(0, 0, 1.f/(1+c), -1),
        glm::vec4(0, 0, -c/(1+c), 0)
    );

    glm::mat4 mat3 = glm::mat4(
        glm::vec4(1, 0, 0, 0),
        glm::vec4(0, 1, 0, 0),
        glm::vec4(0, 0, -2, 0),
        glm::vec4(0, 0, -1, 1)
    );

    return mat3*mat2*mat1;
}

float Camera::getNear() {
    return m_near;
}

float Camera::getFar() {
    return m_far;
}

void Camera::setClipping(float near, float far) {
    m_near = near;
    m_far = far;
    recomputeProjection();
}

void Camera::translate(glm::vec3 direction){
    glm::vec3 horiz = glm::normalize(glm::cross(m_up, m_look));
    glm::vec3 movement = direction.x*horiz + direction.y * m_up + direction.z * glm::normalize(m_look);
    m_pos += movement;
    recomputeView();
}

void Camera::rotate(float vertical, float horizontal){
    glm::mat4 verticalRotate = glm::rotate(glm::mat4(1), vertical, glm::vec3(0, 1, 0));
    glm::mat4 horizontalRotate = glm::rotate(glm::mat4(1), horizontal, glm::normalize(glm::cross(m_up, m_look)));
    m_look = verticalRotate*horizontalRotate*glm::vec4(m_look, 0);
    recomputeView();
}
