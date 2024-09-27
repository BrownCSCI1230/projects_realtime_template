#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glm/glm.hpp>
#include "openglshape.h"

class Cube : public OpenGLShape
{
public:
    Cube(int param1);
    ~Cube();

    void updateParams(int param1, int param2);
    std::vector<float> generateShape();

private:
    void setVertexData();
    void makeTile(glm::vec3 topLeft, glm::vec3 bottomLeft,
                  glm::vec3 bottomRight, glm::vec3 topRight,
                  glm::vec2 topLeftUV, glm::vec2 bottomRightUV);
    void makeFace(glm::vec3 topLeft, glm::vec3 bottomLeft,
                  glm::vec3 bottomRight, glm::vec3 topRight);

    std::vector<float> m_vertexData;
    int m_param1;
};

#endif // CUBE_H
