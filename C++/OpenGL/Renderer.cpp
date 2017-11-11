#include "Renderer.h"

std::ostream & operator<< (std::ostream & os, const glm::vec2 vec)
{
  os << "(" << vec.x << ", " << vec.y << ")";
  return os;
}

Renderer::Renderer(GLFWwindow * window, Shader & basicShader, Shader & textShader, Texture & textFont) : m_window(window), m_basicShader(basicShader), m_textShader(textShader), m_textFont(textFont)
{
  glGenVertexArrays(1, &m_basicVAO);
  glGenBuffers(1, &m_basicVBO);
  glGenBuffers(1, &m_basicEBO);

  glGenVertexArrays(1, &m_textVAO);
  glGenBuffers(1, &m_textVBO);
  glGenBuffers(1, &m_textEBO);

  glBindVertexArray(m_basicVAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_basicVBO);
  glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), m_basicVertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_basicEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), m_basicIndices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  for (unsigned short c = 0; c < 256; ++c)
  {
    float uv_x = (c % 16) / 16.0f;
    float uv_y = (c / 16) / 16.0f;
    m_UVmap[0 + 8 * c] = uv_x + 1.0f / 16.0f - 0.005f;
    m_UVmap[1 + 8 * c] = uv_y + 0.005f;
    m_UVmap[2 + 8 * c] = uv_x + 1.0f / 16.0f - 0.005f;
    m_UVmap[3 + 8 * c] = uv_y + 1.0f / 16.0f;
    m_UVmap[4 + 8 * c] = uv_x;
    m_UVmap[5 + 8 * c] = uv_y + 1.0f / 16.0f;
    m_UVmap[6 + 8 * c] = uv_x;
    m_UVmap[7 + 8 * c] = uv_y + 0.005f;
  }
}

Renderer::~Renderer()
{
  glDeleteVertexArrays(1, &m_basicVAO);
  glDeleteBuffers(1, &m_basicVBO);
  glDeleteBuffers(1, &m_basicEBO);
  glDeleteVertexArrays(1, &m_textVAO);
  glDeleteBuffers(1, &m_textVBO);
  glDeleteBuffers(1, &m_textEBO);
}

void Renderer::render_basic (Object & object, Camera & camera)
{
  int width, height;
  glfwGetFramebufferSize(m_window, &width, &height);

  glm::mat4 model = object.get_model_matrix();
  glm::mat4 view = camera.get_view_matrix();
  glm::mat4 projection;
  if (camera.get_projection_mode() == PERSPECTIVE)
  {
    projection = glm::perspective(glm::radians(camera.get_fov()), ((float)width) / ((float)height), 0.1f, 100.0f);
  }
  else
  {
    projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 10.0f);
  }

  m_basicShader.use();

  m_basicShader.set_matrix4("model", model);
  m_basicShader.set_matrix4("view", view);
  m_basicShader.set_matrix4("projection", projection);
  m_basicShader.set_vector4("ourColor", object.get_color());

  glBindVertexArray(m_basicVAO);
  object.get_texture().use();
  glEnable(GL_DEPTH_TEST);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glDisable(GL_DEPTH_TEST);
  glBindVertexArray(0);
  glUseProgram(0);
}

void Renderer::render_text (const std::string text, const glm::vec4 color, const glm::vec2 position, const glm::vec2 size)
{
  unsigned int textLength = text.length();
  unsigned int vertices = textLength * 16;
  unsigned int indices = textLength * 6;

  for (unsigned int i = 0; i < textLength; ++i)
  {
    char character = text[i];
    m_textVertices[0 + 16 * i] = position.x + i * size.x + size.x;
    m_textVertices[1 + 16 * i] = position.y + size.y;
    m_textVertices[2 + 16 * i] = m_UVmap[0 + 8 * character];
    m_textVertices[3 + 16 * i] = m_UVmap[1 + 8 * character];
    m_textVertices[4 + 16 * i] = position.x + i * size.x + size.x;
    m_textVertices[5 + 16 * i] = position.y;
    m_textVertices[6 + 16 * i] = m_UVmap[2 + 8 * character];
    m_textVertices[7 + 16 * i] = m_UVmap[3 + 8 * character];
    m_textVertices[8 + 16 * i] = position.x + i * size.x;
    m_textVertices[9 + 16 * i] = position.y;
    m_textVertices[10 + 16 * i] = m_UVmap[4 + 8 * character];
    m_textVertices[11 + 16 * i] = m_UVmap[5 + 8 * character];
    m_textVertices[12 + 16 * i] = position.x + i * size.x;
    m_textVertices[13 + 16 * i] = position.y + size.y;
    m_textVertices[14 + 16 * i] = m_UVmap[6 + 8 * character];
    m_textVertices[15 + 16 * i] = m_UVmap[7 + 8 * character];

    m_textIndices[0 + 6 * i] = (0 + 4 * i);
    m_textIndices[1 + 6 * i] = (1 + 4 * i);
    m_textIndices[2 + 6 * i] = (3 + 4 * i);
    m_textIndices[3 + 6 * i] = (1 + 4 * i);
    m_textIndices[4 + 6 * i] = (2 + 4 * i);
    m_textIndices[5 + 6 * i] = (3 + 4 * i);
  }

  m_textShader.use();
  m_textShader.set_vector4("fontColor", color);

  glBindVertexArray(m_textVAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_textVBO);
  glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(float), m_textVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_textEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices * sizeof(unsigned int), m_textIndices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  m_textFont.use();

  glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glUseProgram(0);
}

void Renderer::render_text_beta (const std::string text, const glm::vec4 color, const glm::vec2 position, const glm::vec2 size)
{
  render_text(text, color, position, size);
}
