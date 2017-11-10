#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <iostream>
#include <string>

class Texture
{
private:
  GLuint m_texture;
  int m_width;
  int m_height;
  int m_channels;
public:
  // Default constructor
  Texture ();

  // Load a texture from a file
  Texture (const std::string imageFilePathname, const bool flip = true);
  
  // Clean up
  ~Texture ();

  // Use the texture when rendering
  void use () const;

  // Accessor functions
  GLuint get_texture () const;
  int get_width () const;
  int get_height () const;
  int get_channels () const;
};

#endif
