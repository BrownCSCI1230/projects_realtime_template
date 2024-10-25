#include "shader.h"
#include "utils/debug.h"

#include <iostream>

#define SET_UNIFORM(x, y)                                    \
    do {                                                     \
        if (!setUniform(x, y)) {                             \
            std::cerr << "Failed to set " << x << std::endl; \
        }                                                    \
    } while(0);

Shader::~Shader() {
    if (m_initialized) {
        glDeleteProgram(m_handle);
        glErrorCheck();
    }
}

GLuint Shader::initialize(GLuint handle) {
    m_handle = handle;
    m_initialized = true;
    return m_handle;
}

void Shader::setCameraData(Camera &camera){
    SET_UNIFORM("view", camera.getView());
    SET_UNIFORM("projection", camera.getProjection());
    //SET_UNIFORM("worldSpace_camPos", camera.getWorldSpacePos());
    glErrorCheck();
}

void Shader::setGBufferCameraData(Camera &camera){
    SET_UNIFORM("view", camera.getView());
    SET_UNIFORM("projection", camera.getProjection());
    glErrorCheck();
}

void Shader::setDeferredCameraData(Camera &camera){
    SET_UNIFORM("worldSpace_camPos", camera.getWorldSpacePos());
}

void Shader::setLightData(std::vector<SceneLightData> lights) {
    int numLights = std::min(int(lights.size()), 8);
    SET_UNIFORM("numLights", numLights);
    for(int i = 0; i<numLights; i++){
        if(lights[i].type == LightType::LIGHT_POINT){
            SET_UNIFORM("lightType["+std::to_string(i)+"]", 0);
            SET_UNIFORM("worldSpace_lightPos["+std::to_string(i)+"]", glm::vec3(lights[i].pos));
            SET_UNIFORM("lightColor["+std::to_string(i)+"]", glm::vec3(lights[i].color));
            SET_UNIFORM("lightFunction["+std::to_string(i)+"]", lights[i].function);
        }
        if(lights[i].type == LightType::LIGHT_DIRECTIONAL){
            SET_UNIFORM("lightType["+std::to_string(i)+"]", 1);
            SET_UNIFORM("worldSpace_lightDir["+std::to_string(i)+"]", glm::vec3(lights[i].dir));
            SET_UNIFORM("lightColor["+std::to_string(i)+"]", glm::vec3(lights[i].color));
        }
        if(lights[i].type == LightType::LIGHT_SPOT){
            SET_UNIFORM("lightType["+std::to_string(i)+"]", 2);
            SET_UNIFORM("worldSpace_lightPos["+std::to_string(i)+"]", glm::vec3(lights[i].pos));
            SET_UNIFORM("worldSpace_lightDir["+std::to_string(i)+"]", glm::vec3(lights[i].dir));
            SET_UNIFORM("lightColor["+std::to_string(i)+"]", glm::vec3(lights[i].color));
            SET_UNIFORM("lightFunction["+std::to_string(i)+"]", lights[i].function);
            SET_UNIFORM("angle["+std::to_string(i)+"]", lights[i].angle);
            SET_UNIFORM("penumbra["+std::to_string(i)+"]", lights[i].penumbra);
        }
    }
    glErrorCheck();
}

void Shader::setShapeData(RenderShapeData& shape) {
    SET_UNIFORM("inverseTransposeModel", glm::transpose(glm::inverse(glm::mat3(shape.ctm))));
    SET_UNIFORM("model", shape.ctm);
    SET_UNIFORM("obj_ambient_color", glm::vec3(shape.primitive.material.cAmbient));
    SET_UNIFORM("obj_diffuse_color", glm::vec3(shape.primitive.material.cDiffuse));
    SET_UNIFORM("obj_specular_color", glm::vec3(shape.primitive.material.cSpecular));
    SET_UNIFORM("shininess", shape.primitive.material.shininess);
    glErrorCheck();
}

void Shader::setGlobalData(SceneGlobalData &global) {
    SET_UNIFORM("ka", global.ka);
    SET_UNIFORM("kd", global.kd);
    SET_UNIFORM("ks", global.ks);
    glErrorCheck();
}

void Shader::setPostprocessData(bool perPixel, bool kernelBased, int width, int height) {
    SET_UNIFORM("invertColors", perPixel);
    SET_UNIFORM("sharpenImage", kernelBased);
    SET_UNIFORM("width", width);
    SET_UNIFORM("height", height);
    glErrorCheck();
}

void Shader::setDeferredTextures(){
    SET_UNIFORM("gPosition", 0);
    SET_UNIFORM("gNormal", 1);
    SET_UNIFORM("obj_ambient_color", 2);
    SET_UNIFORM("obj_diffuse_color", 3);
    SET_UNIFORM("obj_specular_color", 4);

    glErrorCheck();
}

bool Shader::setUniform(std::string varName, int value) {
    bind();
    int varLoc = glGetUniformLocation(m_handle, varName.c_str());
    if(varLoc == -1){
        unbind();
        return false;
    }
    glUniform1i(varLoc, value);
    unbind();
    return true;
}

bool Shader::setUniform(std::string varName, float value) {
    bind();
    int varLoc = glGetUniformLocation(m_handle, varName.c_str());
    if(varLoc == -1){
        unbind();
        return false;
    }
    glUniform1f(varLoc, value);
    unbind();
    return true;
}
bool Shader::setUniform(std::string varName, glm::vec3 value) {
    bind();
    int varLoc = glGetUniformLocation(m_handle, varName.c_str());
    if(varLoc == -1){
        unbind();
        return false;
    }
    glUniform3f(varLoc, value.x, value.y, value.z);
    unbind();
    return true;
}
bool Shader::setUniform(std::string varName, glm::mat3 value) {
    bind();
    int varLoc = glGetUniformLocation(m_handle, varName.c_str());
    if(varLoc == -1){
        unbind();
        return false;
    }
    glUniformMatrix3fv(varLoc, 1, GL_FALSE, glm::value_ptr(value));
    unbind();
    return true;
}
bool Shader::setUniform(std::string varName, glm::mat4 value) {
    bind();
    int varLoc = glGetUniformLocation(m_handle, varName.c_str());
    if(varLoc == -1){
        unbind();
        return false;
    }
    glUniformMatrix4fv(varLoc, 1, GL_FALSE, glm::value_ptr(value));
    unbind();
    return true;
}

void Shader::bind() {
    glUseProgram(m_handle);
}

void Shader::unbind() {
    glUseProgram(0);
}
