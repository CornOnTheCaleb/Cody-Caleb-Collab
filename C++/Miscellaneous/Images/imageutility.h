#ifndef IMAGE_UTILITY_H
#define IMAGE_UTILITY_H

#include <iostream>
#include <vector>
#include "image.h"

class ConvolutionKernel
{
  private:
    // Kernel weights
    double * m_weightData;
    std::vector< std::vector<double> > m_data;

    // Sum of all kernel weights
    double m_sum;

    // Dimensions of kernel
    short m_width;
    short m_height;
  public:
    // Default constructor
    ConvolutionKernel ();

    // Constructor with 2D kernel weight array
    ConvolutionKernel (const double ** weights, const unsigned short width, const unsigned short height);

    // Constructor with kernel weight vector
    ConvolutionKernel (const std::vector< std::vector<double> > & data);

    // Get width of kernel
    short get_width () const;

    // Get height of kernel
    short get_height () const;

    // Get kernel sum
    double get_sum () const;

    // Get kernel weight data
    double get_weight (const short row, const short column) const;
};

// Apply operation to all pixels - only given color data
template <typename T>
void apply_operation_rgb (Image & image, T operation)
{
  for (int column = 0; column < image.get_width(); ++column)
  {
    for (int row = 0; row < image.get_height(); ++row)
    {
      unsigned char red, green, blue;
      image.get_pixel(column, row, red, green, blue);
      operation(red, green, blue);
      image.set_pixel(column, row, red, green, blue);
    }
  }
  return;
}

// Apply operation to all pixels - only given pixel position
template <typename T>
void apply_operation_pixel (Image & image, T operation)
{
  for (int column = 0; column < image.get_width(); ++column)
  {
    for (int row = 0; row < image.get_height(); ++row)
    {
      operation(image, column, row);
    }
  }
  return;
}

// Clamp a number if out of specified range
double clamp (const double number, const double lowerBound, const double upperBound);

// Convert a number from one range to another
double convert_range (const double number, const double oldMin, const double oldMax, const double newMin, const double newMax);

// Apply a convolution kernel to image
void apply_convolution (Image & image, const ConvolutionKernel & kernel);

// Apply max pooling operation to downsample image to 1/factor the size
void apply_max_pool (Image & image, const short factor);

// Rotate image
void rotate_clockwise_90 (Image & image);

#endif
