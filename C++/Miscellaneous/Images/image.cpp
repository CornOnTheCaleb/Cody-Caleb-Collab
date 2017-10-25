#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_resize.h>
#include <stb/stb_image_write.h>
#include "image.h"

// Check if valid row and column
bool Image::is_valid_position (const int column, const int row) const
{
  bool isValidColumn = (column >= 0 && column < m_width);
  bool isValidRow = (row >= 0 && row < m_height);
  return (isValidColumn && isValidRow);
}

// Clears everything up
void Image::clear ()
{
  if (m_resized)
  {
    delete[] m_pixelData;
  }
  else
  {
    stbi_image_free(m_pixelData);
  }
  m_pixelData = NULL;
  m_width = 0;
  m_height = 0;
  m_channels = 0;
  m_resized = true;
  return;
}

// Default constructor
Image::Image () : m_pixelData(NULL), m_width(0), m_height(0), m_channels(0), m_resized(true)
{

}

// Constructor with width and height
Image::Image (const int width, const int height, const int channels) : m_pixelData(NULL), m_width(0), m_height(0), m_channels(0), m_resized(true)
{
  if (width > 0 & height > 0 && channels > 0)
  {
    m_pixelData = new unsigned char[width * height * channels];
    m_width = width;
    m_height = height;
    m_channels = channels;
  }
}

// Copy constructor
Image::Image (const Image & image) : m_pixelData(NULL), m_width(0), m_height(0), m_channels(0), m_resized(true)
{
  *this = image;
}

// Operator=
Image & Image::operator= (const Image & image)
{
  if (this != &image)
  {
    clear();
    m_width = image.m_width;
    m_height = image.m_height;
    m_channels = image.m_channels;
    m_pixelData = new unsigned char[m_width * m_height * m_channels];
    for (int i = 0; i < m_width * m_height * m_channels; ++i)
    {
      m_pixelData[i] = image.m_pixelData[i];
    }
    m_resized = true;
  }
  return (*this);
}

// Destructor
Image::~Image ()
{
  clear();
}

// Load data from file, return whether successful
void Image::load_from_file (const char * filename)
{
  clear();
  m_pixelData = stbi_load(filename, &m_width, &m_height, &m_channels, STBI_rgb);
  m_resized = false;
  return;
}

// Save data to image file, return whether successful
void Image::save_to_file (const char * filename)
{
  stbi_write_png(filename, m_width, m_height, m_channels, m_pixelData, 0);
  return;
}

// Resize image
void Image::resize (const int width, const int height)
{
  unsigned char * resized = new unsigned char[width * height * m_channels];
  stbir_resize_uint8(m_pixelData, m_width, m_height, 0, resized, width, height, 0, m_channels);
  if (m_resized)
  {
    delete[] m_pixelData;
  }
  else
  {
    stbi_image_free(m_pixelData);
  }
  m_pixelData = resized;
  m_width = width;
  m_height = height;
  m_resized = true;
  return;
}

// Get width of image
int Image::get_width () const
{
  return m_width;
}

// Get height of image
int Image::get_height () const
{
  return m_height;
}

// Get height of image
int Image::get_channels () const
{
  return m_channels;
}

// Get color values of a particular pixel, return whether successful
bool Image::get_pixel (const int column, const int row, unsigned char & red, unsigned char & green, unsigned char & blue) const
{
  if (is_valid_position(column, row))
  {
    int pixelStartIndex = row * m_width * m_channels + column * m_channels;
    red = m_pixelData[pixelStartIndex + 0];
    green = m_pixelData[pixelStartIndex + 1];
    blue = m_pixelData[pixelStartIndex + 2];
    return true;
  }
  return false;
}

// Set color values of a particular pixel, return whether successful
bool Image::set_pixel (const int column, const int row, const unsigned char red, const unsigned char green, const unsigned char blue)
{
  if (is_valid_position(column, row))
  {
    int pixelStartIndex = row * m_width * m_channels + column * m_channels;
    m_pixelData[pixelStartIndex + 0] = red;
    m_pixelData[pixelStartIndex + 1] = green;
    m_pixelData[pixelStartIndex + 2] = blue;
    return true;
  }
  return false;
}
