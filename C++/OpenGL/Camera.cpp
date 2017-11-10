#include "Camera.h"

Camera::Camera (const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 worldUp, const float fov, const PROJECTION_MODE projectionMode)
{
  set_position(position);
  set_rotation(rotation);
  set_world_up(worldUp);
  set_fov(fov);
  set_projection_mode(projectionMode);
}

Camera::~Camera ()
{

}

void Camera::update_vectors ()
{
  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
  front = glm::rotateX(front, m_rotation.x);
  front = glm::rotateY(front, -m_rotation.y);
  front = glm::rotateZ(front, m_rotation.z);
  m_front = glm::normalize(front);
  m_right = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, m_front));
  m_up = glm::rotate(m_up, m_rotation.z, m_front);
}

void Camera::set_position (const glm::vec3 position)
{
  m_position = position;
}

void Camera::set_rotation (const glm::vec3 rotation)
{
  m_rotation = rotation;
  m_rotation.x = glm::clamp(m_rotation.x, glm::radians(-89.0f), glm::radians(89.0f));
  update_vectors();
}

void Camera::set_world_up (const glm::vec3 worldUp)
{
  m_worldUp = worldUp;
  update_vectors();
}

void Camera::set_fov (const float fov)
{
  m_fov = fov;
}

void Camera::set_projection_mode (const PROJECTION_MODE projectionMode)
{
  m_projectionMode = projectionMode;
}

glm::vec3 Camera::get_position () const
{
  return m_position;
}

glm::vec3 Camera::get_front () const
{
  return m_front;
}

glm::vec3 Camera::get_up () const
{
  return m_up;
}

glm::vec3 Camera::get_right () const
{
  return m_right;
}

glm::vec3 Camera::get_rotation () const
{
  return m_rotation;
}

glm::vec3 Camera::get_world_up () const
{
  return m_worldUp;
}

glm::mat4 Camera::get_view_matrix() const
{
  return glm::lookAt(m_position, m_position + m_front, m_up);
}

float Camera::get_fov () const
{
  return m_fov;
}

PROJECTION_MODE Camera::get_projection_mode () const
{
  return m_projectionMode;
}