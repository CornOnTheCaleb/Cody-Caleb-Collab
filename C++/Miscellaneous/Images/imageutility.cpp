#include "imageutility.h"

// Default constructor
ConvolutionKernel::ConvolutionKernel () : m_sum(0), m_width(0), m_height(0)
{

}

// Constructor with 2D kernel weight array
ConvolutionKernel::ConvolutionKernel (const double ** weights, const unsigned short width, const unsigned short height) : m_sum(0), m_width(width), m_height(height)
{
  m_weightData = new double[width * height];
  for (short row = 0; row < height; ++ row)
  {
    for (short column = 0; column < width; ++column)
    {
      m_weightData[row * width + column] = weights[row][column];
      m_sum += weights[row][column];
    }
  }
}

// Constructor with kernel weight vector
ConvolutionKernel::ConvolutionKernel (const std::vector< std::vector<double> > & data) : m_data(data), m_sum(0), m_width(0), m_height(data.size())
{
  for (short row = 0; row < m_data.size(); ++row)
  {
    if (m_data[row].size() > m_width)
    {
      m_width = m_data[row].size();
    }
    for (short column = 0; column < m_data[row].size(); ++column)
    {
      m_sum += m_data[row][column];
    }
  }
}

// Get width of kernel
short ConvolutionKernel::get_width () const
{
  return m_width;
}

// Get height of kernel
short ConvolutionKernel::get_height () const
{
  return m_height;
}

// Get kernel sum
double ConvolutionKernel::get_sum () const
{
  return m_sum;
}

// Get kernel weight data
double ConvolutionKernel::get_weight (const short row, const short column) const
{
  double weight = 0;
  if (row >= 0 && row < m_data.size() && column >= 0 && column < m_data[row].size())
  {
    weight = m_data[row][column];
  }
  return weight;
}

// Clamp a number if out of specified range
double clamp (const double number, const double lowerBound, const double upperBound)
{
  return (number < lowerBound ? lowerBound : (number > upperBound ? upperBound : number));
}

// Convert a number from one range to another
double convert_range (const double number, const double oldMin, const double oldMax, const double newMin, const double newMax)
{
  return (((number - oldMin) * (newMax - newMin)) / oldMax - oldMin) + newMin;
}


// Apply a convolution kernel to image
void apply_convolution (Image & image, const ConvolutionKernel & kernel)
{
  short marginLeft = static_cast<short>(kernel.get_width() / 2.0 - 0.5);
  short marginRight = static_cast<short>(kernel.get_width() / 2.0);
  short marginTop = static_cast<short>(kernel.get_height() / 2.0 - 0.5);
  short marginBottom = static_cast<short>(kernel.get_height() / 2.0);
  Image processedImage(image.get_width() - marginLeft - marginRight, image.get_height() - marginTop - marginBottom, 3);
  for (int column = 0; column < processedImage.get_width(); ++column)
  {
    for (int row = 0; row < processedImage.get_height(); ++row)
    {
      double regionSumRed = 0;
      double regionSumGreen = 0;
      double regionSumBlue = 0;
      for (short kernelRow = 0; kernelRow < kernel.get_height(); ++kernelRow)
      {
        for (short kernelColumn = 0; kernelColumn < kernel.get_width(); ++kernelColumn)
        {
          unsigned char red, green, blue;
          image.get_pixel(column + kernelColumn, row + kernelRow, red, green, blue);
          double kernelWeight = kernel.get_weight(kernelRow, kernelColumn);
          regionSumRed += (kernelWeight * red);
          regionSumGreen += (kernelWeight * green);
          regionSumBlue += (kernelWeight * blue);
        }
      }
      if (kernel.get_sum() != 0)
      {
        processedImage.set_pixel(column, row, clamp(regionSumRed / kernel.get_sum(), 0, 255), clamp(regionSumGreen / kernel.get_sum(), 0, 255), clamp(regionSumBlue / kernel.get_sum(), 0, 255));
      }
      else
      {
        processedImage.set_pixel(column, row, clamp(regionSumRed, 0, 255), clamp(regionSumGreen, 0, 255), clamp(regionSumBlue, 0, 255));
      }
    }
  }
  image = processedImage;
  return;
}

// Apply max pooling operation to downsample image to 1/factor the size
void apply_max_pool (Image & image, const short factor)
{
  Image processedImage(image.get_width() / factor, image.get_height() / factor, 3);
  for (short column = 0; column < processedImage.get_width(); ++column)
  {
    for (short row = 0; row < processedImage.get_height(); ++row)
    {
      unsigned char maxRed = 0, maxGreen = 0, maxBlue = 0;
      for (short i = 0; i < factor; ++i)
      {
        for (short j = 0; j < factor; ++j)
        {
          unsigned char red, green, blue;
          image.get_pixel(column * factor + i, row * factor + j, red, green, blue);
          if (red > maxRed)
          {
            maxRed = red;
          }
          if (green > maxGreen)
          {
            maxGreen = green;
          }
          if (blue > maxBlue)
          {
            maxBlue = blue;
          }
        }
      }
      processedImage.set_pixel(column, row, maxRed, maxGreen, maxBlue);
    }
  }
  image = processedImage;
  return;
}

// Rotate image
void rotate_clockwise_90 (Image & image)
{
  Image processedImage(image.get_height(), image.get_width(), 3);
  for (short column = 0; column < processedImage.get_width(); ++column)
  {
    for (short row = 0; row < processedImage.get_height(); ++row)
    {
      unsigned char red, green, blue;
      image.get_pixel(row, image.get_height() - column, red, green, blue);
      processedImage.set_pixel(column, row, red, green, blue);
    }
  }
  image = processedImage;
  return;
}
