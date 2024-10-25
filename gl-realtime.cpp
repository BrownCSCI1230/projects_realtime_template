#include "gl-realtime.h"
#include "utils/shaderloader.h"
#include "shapes/cone.h"
#include "shapes/cube.h"
#include "shapes/cylinder.h"
#include "shapes/sphere.h"

#include <GL/glew.h>
#include <iostream>

GlRealtime::GlRealtime(size_t width, size_t height, double device_pixel_ratio) :
    m_gl_initializer(),
    m_devicePixelRatio(device_pixel_ratio),
    m_screen_width(int32_t(width * device_pixel_ratio)),
    m_screen_height(int32_t(height * device_pixel_ratio))
{
    // Allows OpenGL to draw objects appropriately on top of one another
    glEnable(GL_DEPTH_TEST);
    // Tells OpenGL to only draw the front face
    glEnable(GL_CULL_FACE);
    // Tells OpenGL how big the screen is
    glViewport(0, 0, m_screen_width, m_screen_height);

    // Students: anything requiring OpenGL calls when the program starts should be done here

    createShaders();
    createFullScreenQuad();
    //initVBuffers();

    glClearColor(1, 1, 1, 0);
}

GlRealtime::~GlRealtime() {}

// void initVBuffers() {

// }

void GlRealtime::resize(size_t width, size_t height) {
    m_screen_width = width * m_devicePixelRatio;
    m_screen_height = height * m_devicePixelRatio;

    glViewport(0, 0, m_screen_width, m_screen_height);
    // Students: anything requiring OpenGL calls when the program starts should be done here
    // TA Solution:
    m_camera.resize(m_screen_width, m_screen_height);
    //m_fbo.finish();
    //m_fbo.initialize(m_screen_width, m_screen_height);

    // Set Camera Data
    m_phong_shader.setCameraData(m_camera);
}

void GlRealtime::createFullScreenQuad() {
    static const std::vector<GLfloat> fullscreen_quad_data =
        {   // x, y, z, u, v    //
            -1.0f,  1.0f, 0.0f,
            0.0f,  1.0f,
            -1.0f, -1.0f, 0.0f,
            0.0f,  0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  0.0f,
            1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,
            -1.0f,  1.0f, 0.0f,
            0.0f,  1.0f
        };

    m_quad_vbo.setData(fullscreen_quad_data);
    m_quad_vao.setData(m_quad_vbo, VAOAttrib::POS | VAOAttrib::UV);
}

void GlRealtime::createShaders() {
    GLuint default_shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");
    m_phong_shader.initialize(default_shader);
}

void GlRealtime::paint() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phong_shader.bind();

    //m_fbo.bindFBO();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update Camera Data
    m_phong_shader.setCameraData(m_camera);
    // Set + Draw Shapes
    for(int i = 0; i < m_render_data.shapes.size(); i++){
        RenderShapeData& shape = m_render_data.shapes[i];
        m_phong_shader.setShapeData(shape);
        m_phong_shader.bind();
        m_shapeVAOs[shape.primitive.type].draw();
        m_phong_shader.unbind();
    }

    //m_fbo.unbindFBO();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // m_postprocessShader.setPostprocessData(settings.perPixelFilter, settings.kernelBasedFilter, m_s    creen_width, m_screen_height);
    // m_fbo.bindTexture();
    // m_postprocessShader.bind();
    // m_fullscreenQuadVAO.bind();
    // m_fullscreenQuadVAO.draw();
    // m_fullscreenQuadVAO.unbind();
    // m_postprocessShader.unbind();
    // m_fbo.unbindTexture();

    m_quad_vao.draw();
    m_phong_shader.unbind();
}

void GlRealtime::updateShapes() {
    // Create shapes
    Cube cube = Cube(m_tesselation_param1);
    m_shapeVBOs[PrimitiveType::PRIMITIVE_CUBE].setData(cube.generateShape());
    m_shapeVAOs[PrimitiveType::PRIMITIVE_CUBE].setData(m_shapeVBOs[PrimitiveType::PRIMITIVE_CUBE], VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);

    Cone cone = Cone(m_tesselation_param1, m_tesselation_param2);
    m_shapeVBOs[PrimitiveType::PRIMITIVE_CONE].setData(cone.generateShape());
    m_shapeVAOs[PrimitiveType::PRIMITIVE_CONE].setData(m_shapeVBOs[PrimitiveType::PRIMITIVE_CONE], VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);

    Cylinder cylinder = Cylinder(m_tesselation_param1, m_tesselation_param2);
    m_shapeVBOs[PrimitiveType::PRIMITIVE_CYLINDER].setData(cylinder.generateShape());
    m_shapeVAOs[PrimitiveType::PRIMITIVE_CYLINDER].setData(m_shapeVBOs[PrimitiveType::PRIMITIVE_CYLINDER], VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);

    Sphere sphere = Sphere(m_tesselation_param1, m_tesselation_param2);
    m_shapeVBOs[PrimitiveType::PRIMITIVE_SPHERE].setData(sphere.generateShape());
    m_shapeVAOs[PrimitiveType::PRIMITIVE_SPHERE].setData(m_shapeVBOs[PrimitiveType::PRIMITIVE_SPHERE], VAOAttrib::POS | VAOAttrib::NORM | VAOAttrib::UV);

}

void GlRealtime::setStaticSceneUniforms() {
    // Set Camera Data
    m_phong_shader.setCameraData(m_camera);

    // Set Global Coefficients
    m_phong_shader.setGlobalData(m_render_data.globalData);

    // Set Lights
    m_phong_shader.setLightData(m_render_data.lights);
}

void GlRealtime::loadScene(const std::string& filepath, int near, int far) {
    SceneParser::parse(filepath, m_render_data); // Parse scene data
    m_camera.init(
        m_render_data,
        m_screen_width,
        m_screen_height,
        near,
        far
    ); // Initialize camera
    updateShapes();
    setStaticSceneUniforms();
}

void GlRealtime::settingsChanged() {
    if (settings.shapeParameter1 != m_tesselation_param1 ||
        settings.shapeParameter2 != m_tesselation_param2
    ){
        m_tesselation_param1 = settings.shapeParameter1;
        m_tesselation_param2 = settings.shapeParameter2;
        updateShapes();
    }
    if (settings.nearPlane != m_camera.getNear() ||
        settings.farPlane != m_camera.getFar()
    ){
        m_camera.setClipping(settings.nearPlane, settings.farPlane);

        // Set Camera Data
        m_phong_shader.setCameraData(m_camera);
    }
}
