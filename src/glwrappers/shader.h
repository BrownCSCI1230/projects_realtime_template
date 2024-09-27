#pragma once

#include "GL/glew.h"
#include "../utils/sceneparser.h"
#include "../camera.h"

class Shader
{
public:
    Shader() : m_initialized(false) {}
    ~Shader();

    GLuint initialize(GLuint handle);
    void bind();
    void unbind();

    void setCameraData(Camera& camera);
    void setLightData(std::vector<SceneLightData> lights);
    void setShapeData(RenderShapeData& shape);
    void setGlobalData(SceneGlobalData& global);
    void setPostprocessData(bool perPixel, bool kernelBased, int width, int height);
    void setGBufferCameraData(Camera& camera);
    void setDeferredCameraData(Camera& camera);
    void setDeferredTextures();

    bool setUniform(std::string varName, int value);
    bool setUniform(std::string varName, float value);
    bool setUniform(std::string varName, glm::vec3 value);
    bool setUniform(std::string varName, glm::mat3 value);
    bool setUniform(std::string varName, glm::mat4 value);

private:
    bool   m_initialized;
    GLuint m_handle;
};
