#ifndef CONE_H
#define CONE_H

#include <vector>
#include <glm/glm.hpp>
#include "openglshape.h"

class Cone: public OpenGLShape
{
public:
    Cone(int param1, int param2);
    ~Cone();

    void updateParams(int param1, int param2);
    std::vector<float> generateShape();

private:
    glm::vec3 cylToCartesian(float theta, float rho, float height);
    void setVertexData();

    std::vector<float> m_vertexData;
    int m_param1;
    int m_param2;
};

#endif // CONE_H
