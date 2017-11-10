#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

class Shader
{
private:
  // Id of shader program
  int m_program;
public:
  // Default constructor
  Shader ();

  // Load shader from files containing GLSL code
  Shader (const std::string vertexShaderFilePathname, const std::string fragmentShaderFilePathname);

  // Clean up
  ~Shader ();

  // Use the shader when rendering
  void use () const;

  // Used to set values for uniform variables in shader code
  void set_bool (const std::string name, const bool value) const;
  void set_int (const std::string name, const int value) const;
  void set_float (const std::string name, const float value) const;
  void set_matrix4 (const std::string name, const glm::mat4 value) const;
  void set_vector4 (const std::string name, const glm::vec4 value) const;

  // Accessor function(s)
  int get_program () const;
};

#endif
