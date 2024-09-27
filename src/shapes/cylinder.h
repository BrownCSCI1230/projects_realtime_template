#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include <glm/glm.hpp>
#include "openglshape.h"

class Cylinder: public OpenGLShape
{
public:
    Cylinder(int param1, int param2);
    ~Cylinder();

    void updateParams(int param1, int param2);
    std::vector<float> generateShape();

private:
    glm::vec3 cylToCartesian(float theta, float rho, float height);
    void setVertexData();

    std::vector<float> m_vertexData;
    int m_param1;
    int m_param2;
};

#endif // CYLINDER_H
