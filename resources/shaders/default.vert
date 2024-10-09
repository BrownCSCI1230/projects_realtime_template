#version 330 core

layout (location = 0) in vec3 objSpace_pos;
//layout (location = 1) in vec3 objSpace_norm;
layout (location = 2) in vec2 uv_coords;

// uniform mat4 model, view, projection;

// uniform mat3 inverseTransposeModel;

// out vec3 worldSpace_pos;
// out vec3 worldSpace_norm;
// out vec2 uv;

void main() {
    // worldSpace_pos = vec3(model*vec4(objSpace_pos, 1.0));
    // //worldSpace_norm = inverseTransposeModel*objSpace_norm;
    // uv = uv_coords;

    // gl_Position = projection*view*model*vec4(objSpace_pos, 1.0);

    gl_Position = vec4(objSpace_pos, 1.f);
}
