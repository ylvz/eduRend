#include "Camera.h"

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const vec3f& direction) noexcept
{
	m_position += direction;
}

void Camera::UpdateRotation(long mousedx, long mousedy, float sensitivity) noexcept
{
    // Apply the sensitivity factor to the mouse movement
    m_yaw += mousedx * sensitivity;
    m_pitch -= mousedy * sensitivity;

    // Constrain the pitch to prevent the camera from flipping upside down
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;
}


mat4f Camera::WorldToViewMatrix() const noexcept
{
	// Create the rotation matrix for yaw and pitch
	mat4f rotation = mat4f::rotation(0.0f, m_yaw, m_pitch);

	// Apply translation and rotation (the rightmost matrix is applied first)
	return rotation * mat4f::translation(-m_position);
}

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}
