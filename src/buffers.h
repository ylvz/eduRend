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
    vec4f ambient;
    vec4f diffuse;
    vec4f specular;
    float shininess;
    float padding[3]; // Ensure 16-byte alignment
};