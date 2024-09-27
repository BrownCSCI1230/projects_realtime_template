#include "sceneparser.h"
#include "scenefilereader.h"
#include <glm/gtx/transform.hpp>

#include <chrono>
#include <iostream>

void dfsParseSceneNode(RenderData &renderData, SceneNode *node, glm::mat4 matrix) {
    if (node == nullptr) {
        return;
    }
    for (auto transform : node->transformations) {
        glm::mat4 transMatrix(1.0f);
        switch (transform->type) {
            case TransformationType::TRANSFORMATION_TRANSLATE:
                {
                    transMatrix = glm::translate(transform->translate);
                    break;
                }
            case TransformationType::TRANSFORMATION_SCALE:
                {
                    transMatrix = glm::scale(transform->scale);
                    break;
                }
            case TransformationType::TRANSFORMATION_ROTATE:
                {
                    transMatrix = glm::rotate(transform->angle, transform->rotate);
                    break;
                }
            case TransformationType::TRANSFORMATION_MATRIX:
                {
                    transMatrix = transform->matrix;
                    break;
                }
            default:
                break;
        }
        // Note the order of multiplication
        matrix = matrix * transMatrix;
    }
    for (auto primitive : node->primitives) {
        RenderShapeData shape = {.primitive = *primitive, .ctm = matrix};
        renderData.shapes.emplace_back(shape);
    }
    for (auto light : node->lights) {
        SceneLightData lightFull = {
            .id = light->id,
            .type = light->type,
            .color = light->color,
            .function = light->function,
            .pos = matrix * glm::vec4(0.f, 0.f, 0.f, 1.f), // note order of multiplication
            .dir = matrix * light->dir, // same here
            .penumbra = light->penumbra,
            .angle = light->angle,
            .width = light->width,
            .height = light->height};

        renderData.lights.emplace_back(lightFull);
    }
    for (SceneNode *child : node->children) {
        dfsParseSceneNode(renderData, child, matrix);
    }
    return;
}

bool SceneParser::parse(std::string filepath, RenderData &renderData) {
    ScenefileReader fileReader = ScenefileReader(filepath);
    bool success = fileReader.readJSON();
    if (!success) {
        return false;
    }

    // Task 4: populate renderData with global data, lights, and camera data
    renderData.cameraData = fileReader.getCameraData();
    renderData.globalData = fileReader.getGlobalData();
    renderData.lights.clear();
    renderData.shapes.clear();

    // Task 5: populate renderData's list of primitives and their transforms.
    //         This will involve traversing the scene graph, and we recommend you
    //         create a helper function to do so!
    SceneNode *root = fileReader.getRootNode();
    glm::mat4 matrix(1.0f);
    dfsParseSceneNode(renderData, root, matrix);

    return true;
}
