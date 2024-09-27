#include "cylinder.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

Cylinder::Cylinder(int param1, int param2):
    m_param1(glm::max(1, param1)),
    m_param2(glm::max(3, param2))
{
    setVertexData();
}

void Cylinder::updateParams(int param1, int param2)
{
    m_vertexData = std::vector<float>();
    m_param1 = glm::max(1, param1);
    m_param2 = glm::max(3, param2);
    setVertexData();
}

Cylinder::~Cylinder() {
}

glm::vec3 Cylinder::cylToCartesian(float theta, float rho, float height) {
    return glm::vec3(glm::cos(theta) * rho,
                     height,
                     glm::sin(theta) * rho);
}

void Cylinder::setVertexData() {
    // TA SOLUTION
    float thetaStep = 2 * glm::pi<float>() / m_param2;
    float zStep = 1.0 / m_param1;
    float radius = 0.5;
    for (int i = 0; i < m_param1; i++) {
        // z increases from -0.5 to 0.5
        float z = i * zStep - 0.5;
        float nextZ = (i + 1) * zStep - 0.5;
        for (int j = 0; j < m_param2; j++) {
            float theta = j * thetaStep;
            float nextTheta = (j + 1) * thetaStep;
            glm::vec3 bottomRight = cylToCartesian(theta, radius, z);
            glm::vec3 bottomLeft = cylToCartesian(nextTheta, radius, z);
            glm::vec3 topRight = cylToCartesian(theta, radius, nextZ);
            glm::vec3 topLeft = cylToCartesian(nextTheta, radius, nextZ);
            // normals
            glm::vec3 bottomLeftNormal = glm::normalize(glm::vec3(bottomLeft.x, 0, bottomLeft.z));
            glm::vec3 bottomRightNormal = glm::normalize(glm::vec3(bottomRight.x, 0, bottomRight.z));
            glm::vec3 topLeftNormal = glm::normalize(glm::vec3(topLeft.x, 0, topLeft.z));
            glm::vec3 topRightNormal = glm::normalize(glm::vec3(topRight.x, 0, topRight.z));
            // uv
            float uleft = theta/(2 * glm::pi<float>());
            float uright = nextTheta/(2 * glm::pi<float>());
            float vtop = 2 * radius * (i + 1) / m_param1;
            float vbot = 2 * radius * i / m_param1;
            // body bottom triangle
            insertVec3(m_vertexData, topLeft);
            insertVec3(m_vertexData, topLeftNormal);
            insertVec2(m_vertexData, glm::vec2(uleft,vtop));
            insertVec3(m_vertexData, bottomLeft);
            insertVec3(m_vertexData, bottomLeftNormal);
            insertVec2(m_vertexData, glm::vec2(uleft,vbot));
            insertVec3(m_vertexData, bottomRight);
            insertVec3(m_vertexData, bottomRightNormal);
            insertVec2(m_vertexData, glm::vec2(uright,vbot));
            // body top triangle
            insertVec3(m_vertexData, topLeft);
            insertVec3(m_vertexData, topLeftNormal);
            insertVec2(m_vertexData, glm::vec2(uleft,vtop));
            insertVec3(m_vertexData, bottomRight);
            insertVec3(m_vertexData, bottomRightNormal);
            insertVec2(m_vertexData, glm::vec2(uright,vbot));
            insertVec3(m_vertexData, topRight);
            insertVec3(m_vertexData, topRightNormal);
            insertVec2(m_vertexData, glm::vec2(uright,vtop));
            // top cap triangle
            if (i == m_param1 - 1) {
                glm::vec3 topCapNormal = glm::vec3(0, 1, 0);
                insertVec3(m_vertexData, topLeft);
                insertVec3(m_vertexData, topCapNormal);
                insertVec2(m_vertexData, glm::vec2(uleft,vtop));
                insertVec3(m_vertexData, topRight);
                insertVec3(m_vertexData, topCapNormal);
                insertVec2(m_vertexData, glm::vec2(uright,vtop));
                insertVec3(m_vertexData, glm::vec3(0, 0.5, 0));
                insertVec3(m_vertexData, topCapNormal);
                insertVec2(m_vertexData, glm::vec2(0.5,0.5));
            }
            // bottom cap triangle
            if (i == 0) {
                glm::vec3 bottomCapNormal = glm::vec3(0, -1, 0);
                insertVec3(m_vertexData, bottomRight);
                insertVec3(m_vertexData, bottomCapNormal);
                insertVec2(m_vertexData, glm::vec2(uright,vbot));
                insertVec3(m_vertexData, bottomLeft);
                insertVec3(m_vertexData, bottomCapNormal);
                insertVec2(m_vertexData, glm::vec2(uleft,vbot));
                insertVec3(m_vertexData, glm::vec3(0, -0.5, 0));
                insertVec3(m_vertexData, bottomCapNormal);
                insertVec2(m_vertexData, glm::vec2(0.5,0.5));
            }
        }
    }
}

std::vector<float> Cylinder::generateShape()
{
    return m_vertexData;
}
