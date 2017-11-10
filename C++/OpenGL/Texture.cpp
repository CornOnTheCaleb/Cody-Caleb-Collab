#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture () : m_texture(0), m_width(0), m_height(0), m_channels(0)
{

}

Texture::Texture (const std::string imageFilePathname, const bool flip) : Texture()
{
  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(flip);

  unsigned char * data = stbi_load(imageFilePathname.c_str(), &m_width, &m_height, &m_channels, 0);
  if (data)
  {
    GLenum mode = (m_channels == 4 ? GL_RGBA : GL_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, m_width, m_height, 0, mode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture (\"" << imageFilePathname << "\")!" << std::endl;
  }
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::~Texture ()
{
  glDeleteTextures(1, &m_texture);
}

void Texture::use () const
{
  glBindTexture(GL_TEXTURE_2D, m_texture);
}

GLuint Texture::get_texture () const
{
  return m_texture;
}

int Texture::get_width () const
{
  return m_width;
}

int Texture::get_height () const
{
  return m_height;
}

int Texture::get_channels () const
{
  return m_channels;
}
