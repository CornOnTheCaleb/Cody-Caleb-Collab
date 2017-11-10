#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

enum PROJECTION_MODE
{
  PERSPECTIVE,
  ORTHOGONAL
};

class Camera
{
private:
  glm::vec3 m_position;
  glm::vec3 m_rotation; // pitch, yaw, roll
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_worldUp;
  float m_fov;
  PROJECTION_MODE m_projectionMode;
private:
  void update_vectors ();
public:
  // Constructor
  Camera (const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), const float fov = 45.0f, const PROJECTION_MODE projectionMode = PERSPECTIVE);

  // Clean up
  ~Camera ();

  // Mutator functions
  void set_position (const glm::vec3 position);
  void set_rotation (const glm::vec3 rotation);
  void set_world_up (const glm::vec3 worldUp);
  void set_fov (const float fov);
  void set_projection_mode (const PROJECTION_MODE projectionMode);

  // Accessor functions
  glm::vec3 get_position () const;
  glm::vec3 get_front () const;
  glm::vec3 get_up () const;
  glm::vec3 get_right () const;
  glm::vec3 get_rotation () const;
  glm::vec3 get_world_up () const;
  float get_fov () const;
  PROJECTION_MODE get_projection_mode () const;

  glm::mat4 get_view_matrix() const;
};

#endif
