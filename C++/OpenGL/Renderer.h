#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"

class Renderer
{
private:
  GLFWwindow * m_window;

  Shader m_basicShader;
  GLuint m_basicVAO;
  GLuint m_basicVBO;
  GLuint m_basicEBO;

  float m_basicVertices[20] = {
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
  };
  unsigned int m_basicIndices[6] = {
    0, 1, 3,
    1, 2, 3
  };
  
  Shader m_textShader;
  Texture m_textFont;
  GLuint m_textVAO;
  GLuint m_textVBO;
  GLuint m_textEBO;

  float m_textVertices[256 * 16];
  unsigned int m_textIndices[256 * 6];
  float m_UVmap[256 * 8];
public:
  // Constructor
  Renderer(GLFWwindow * window, Shader & basicShader, Shader & textShader, Texture & textFont);

  // Clean up
  ~Renderer();

  // Render an object
  void render_basic (Object & object, Camera & camera);

  // Render a text in 2D
  void render_text (const std::string text, const glm::vec4 color, const glm::vec2 position, const glm::vec2 size);

  void render_text_beta (const std::string text, const glm::vec4 color, const glm::vec2 position, const glm::vec2 size);
};

#endif
