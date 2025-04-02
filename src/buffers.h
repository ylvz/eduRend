// buffers.h
#pragma once
#include "vec/mat.h"

// Constant buffer for transformations
struct TransformationBuffer {
    linalg::mat4f ModelToWorldMatrix;
    linalg::mat4f WorldToViewMatrix;
    linalg::mat4f ProjectionMatrix;
};

// Constant buffer for lighting and camera position
struct LightBuffer {
    vec4f LightPosition;
    vec4f CameraPosition;
};

// Constant buffer for material properties
struct MaterialBuffer {
    vec4f ambient;      // 16 bytes
    vec4f diffuse;      // 16 bytes
    vec4f specular;     // 16 bytes
    vec4f shininess;    // 16 bytes
};

