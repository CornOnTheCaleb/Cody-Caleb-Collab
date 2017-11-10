#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

#include "Texture.h"

class Object
{
private:
  Texture m_texture;

  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_size;
  glm::vec4 m_color;

  glm::mat4 m_modelMatrix;
private:
  void update_model_matrix ();
public:
  // Default constructor
  Object ();

  // Constructor with all elements
  Object (const Texture & texture, const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), const glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  // Clean up
  ~Object ();

  // Mutator functions
  void set_texture (const Texture & texture);
  void set_position (const glm::vec3 position);
  void set_rotation (const glm::vec3 rotation);
  void set_size (const glm::vec3 size);
  void set_color (const glm::vec4 color);

  // Accessor functions
  const Texture & get_texture () const;
  glm::vec3 get_position () const;
  glm::vec3 get_rotation () const;
  glm::vec3 get_size () const;
  glm::vec4 get_color () const;

  glm::mat4 get_model_matrix () const;
};

#endif
