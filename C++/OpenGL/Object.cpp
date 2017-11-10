#include "Object.h"

Object::Object () : m_texture(Texture()), m_position(glm::vec3(0.0f, 0.0f, 0.0f)), m_rotation(glm::vec3(0.0f, 0.0f, 0.0f)), m_size(glm::vec3(1.0f, 1.0f, 1.0f)), m_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{

}

Object::Object (const Texture & texture, const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 size, const glm::vec4 color)
{
  set_texture(texture);
  set_position(position);
  set_rotation(rotation);
  set_size(size);
  set_color(color);
}


Object::~Object ()
{

}

void Object::set_texture (const Texture & texture)
{
  m_texture = texture;
}

void Object::set_position (const glm::vec3 position)
{
  m_position = position;
  update_model_matrix();
}

void Object::set_rotation (const glm::vec3 rotation)
{
  m_rotation = rotation;
  update_model_matrix();
}

void Object::set_size (const glm::vec3 size)
{
  m_size = size;
  update_model_matrix();
}

void Object::set_color (const glm::vec4 color)
{
  m_color = color;
}

const Texture & Object::get_texture () const
{
  return m_texture;

}

glm::vec3 Object::get_position () const
{
  return m_position;
}

glm::vec3 Object::get_rotation () const
{
  return m_rotation;
}

glm::vec3 Object::get_size () const
{
  return m_size;
}

glm::vec4 Object::get_color () const
{
  return m_color;
}

void Object::update_model_matrix ()
{
  glm::mat4 model;
  model = glm::translate(model, m_position);
  model = glm::rotate(model, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, m_size);
  m_modelMatrix = model;
}

glm::mat4 Object::get_model_matrix () const
{
  return m_modelMatrix;
}