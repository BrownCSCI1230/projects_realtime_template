#include "cone.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


Cone::Cone(int param1, int param2) :
    m_param1(glm::max(1, param1)),
    m_param2(glm::max(3, param2))
{
    setVertexData();
}

void Cone::updateParams(int param1, int param2)
{
    m_vertexData = std::vector<float>();
    m_param1 = glm::max(1, param1);
    m_param2 = glm::max(3, param2);
    setVertexData();
}

Cone::~Cone()
{

}

glm::vec3 Cone::cylToCartesian(float theta, float rho, float height) {
    return glm::vec3(glm::cos(theta) * rho,
                     height,
                     glm::sin(theta) * rho);
}

void Cone::setVertexData() {
    // TA SOLUTION
    float thetaStep = 2 * glm::pi<float>() / m_param2;
    float zStep = 1.0 / m_param1;
    for (int i = 0; i < m_param1; i++) {
        // z increases from -0.5 to 0.5
        float z = i * zStep - 0.5;
        float nextZ = (i + 1) * zStep - 0.5;
        for (int j = 0; j < m_param2; j++) {
            float theta = j * thetaStep;
            float nextTheta = (j + 1) * thetaStep;
            // radius decreases from 0.5 to 0
            float radius = 0.5 * (0.5 - z);
            float nextRadius = 0.5 * (0.5 - nextZ);
            glm::vec3 bottomRight = cylToCartesian(theta, radius, z);
            glm::vec3 bottomLeft = cylToCartesian(nextTheta, radius, z);
            glm::vec3 topRight = cylToCartesian(theta, nextRadius, nextZ);
            glm::vec3 topLeft = cylToCartesian(nextTheta, nextRadius, nextZ);
            // normals
            glm::vec3 d1 = glm::normalize(bottomLeft - topLeft);
            glm::vec3 d2 = glm::normalize(bottomRight - topRight);
            glm::vec3 leftNormal = glm::normalize(glm::vec3(d1.x,-d1.y,d1.z));
            glm::vec3 rightNormal = glm::normalize(glm::vec3(d2.x,-d2.y,d2.z));
            leftNormal = glm::vec3(glm::rotate(glm::radians(90.0f),glm::cross(d1, leftNormal)) * glm::vec4(d1,0));
            rightNormal = glm::vec3(glm::rotate(glm::radians(90.0f),glm::cross(d2, rightNormal)) * glm::vec4(d2,0));
            // uv (TODO: fix)
            float uleft = theta/(2 * glm::pi<float>());
            float uright = nextTheta/(2 * glm::pi<float>());
            float vtop = 2 * radius * (i + 1) / m_param1;
            float vbot = 2 * radius * i / m_param1;
            // tip normal is the same as implicit cone normal, gradient of x^2 + z^2 - ((0.5-y)/2)^2 = 0
            float thetaMid = theta + 0.5*thetaStep;
            glm::vec3 implicitBottomPoint = glm::vec3(0.5*glm::cos(thetaMid), -0.5, 0.5*glm::sin(thetaMid));
            glm::vec3 tipNormal = glm::normalize(glm::vec3(2.f*implicitBottomPoint.x, 0.25 - implicitBottomPoint.y / 2.f, 2.f*implicitBottomPoint.z));
            // cone tip special case
            // body bottom triangle
            insertVec3(m_vertexData, topLeft);
            if (i == m_param1 - 1) {
                insertVec3(m_vertexData, tipNormal);
            } else {
                insertVec3(m_vertexData, leftNormal);
            }
            insertVec2(m_vertexData, glm::vec2(uleft,vtop));
            insertVec3(m_vertexData, bottomLeft);
            insertVec3(m_vertexData, leftNormal);
            insertVec2(m_vertexData, glm::vec2(uleft,vbot));
            insertVec3(m_vertexData, bottomRight);
            insertVec3(m_vertexData, rightNormal);
            insertVec2(m_vertexData, glm::vec2(uright,vbot));
            // body top triangle
            if (i != m_param1 - 1) {
                insertVec3(m_vertexData, topLeft);
                insertVec3(m_vertexData, leftNormal);
                insertVec2(m_vertexData, glm::vec2(uleft,vtop));
                insertVec3(m_vertexData, bottomRight);
                insertVec3(m_vertexData, rightNormal);
                insertVec2(m_vertexData, glm::vec2(uright,vbot));
                insertVec3(m_vertexData, topRight);
                insertVec3(m_vertexData, rightNormal);
                insertVec2(m_vertexData, glm::vec2(uright,vtop));
            }
            // base triangle
            if (i == 0) {
                glm::vec3 baseNormal = glm::vec3(0, -1, 0);
                glm::vec3 baseCenter = glm::vec3(0, -0.5, 0);
                insertVec3(m_vertexData, baseCenter);
                insertVec3(m_vertexData, baseNormal);
                insertVec2(m_vertexData, glm::vec2(0.5,0.5));
                insertVec3(m_vertexData, bottomRight);
                insertVec3(m_vertexData, baseNormal);
                insertVec2(m_vertexData, glm::vec2(uright,vbot));
                insertVec3(m_vertexData, bottomLeft);
                insertVec3(m_vertexData, baseNormal);
                insertVec2(m_vertexData, glm::vec2(uleft,vbot));
            }
        }
    }
}

std::vector<float> Cone::generateShape()
{
    return m_vertexData;
}
