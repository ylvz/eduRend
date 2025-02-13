
#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vec\vec.h"
#include "vec\mat.h"

class Camera
{
public:
    inline constexpr Camera(float vertical_fov, float aspect_ratio, float near_plane, float far_plane) noexcept
        : m_vertical_fov(vertical_fov), m_aspect_ratio(aspect_ratio), m_near_plane(near_plane), m_far_plane(far_plane), m_position(0.0f), m_yaw(0.0f), m_pitch(0.0f) {}

    void MoveTo(const linalg::vec3f& position) noexcept;
    void Move(const linalg::vec3f& direction) noexcept;

    inline void SetAspect(float aspect_ratio) noexcept { m_aspect_ratio = aspect_ratio; }

    linalg::mat4f WorldToViewMatrix() const noexcept;
    linalg::mat4f ProjectionMatrix() const noexcept;

    // New method for updating the camera's rotation based on mouse input
    void UpdateRotation(long mousedx, long mousedy, float sensitivity) noexcept;

private:
    // Camera parameters
    float m_vertical_fov;
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;

    // Position of the camera in world space
    linalg::vec3f m_position;

    // Rotation angles (yaw and pitch)
    float m_yaw;
    float m_pitch;
};

#endif