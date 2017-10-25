#include <iostream>
#include <cstdlib>
#include "image.h"
#include "imageutility.h"

int main (int argc, char ** argv)
{
  Image image;
  image.load_from_file(argv[1]);
  image.resize(atoi(argv[2]), atoi(argv[3]));
  auto clear = [] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    red = 0; green = 0; blue = 0; return;
  };
  auto invert = [] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    red = 255 - red; green = 255 - green; blue = 255 - blue; return;
  };
  auto grayscale = [] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    unsigned char gray = (0.3 * red) + (0.59 * green) + (0.11 * blue);
    red = gray; green = gray; blue = gray; return;
  };
  auto isolate_red = [] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    green = 0; blue = 0; return;
  };
  auto isolate_green = [] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    red = 0; blue = 0; return;
  };
  auto isolate_blue = [] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    red = 0; green = 0; return;
  };
  const unsigned short THRESHOLD_LEVEL = 128;
  auto threshold_below = [=] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    red = (red < THRESHOLD_LEVEL ? 0 : red); green = (green < THRESHOLD_LEVEL ? 0 : green); blue = (blue < THRESHOLD_LEVEL ? 0 : blue); return;
  };
  auto threshold_above = [=] (unsigned char & red, unsigned char & green, unsigned char & blue) {
    red = (red > THRESHOLD_LEVEL ? 255 : red); green = (green > THRESHOLD_LEVEL ? 255 : green); blue = (blue > THRESHOLD_LEVEL ? 255 : blue); return;
  };

  ConvolutionKernel edgeDetection({{1, 1, 1}, {1, -8, 1}, {1, 1, 1}});
  ConvolutionKernel gaussianBlur({{1, 2, 1}, {2, 4, 2}, {1, 2, 1}});
  ConvolutionKernel meanBlur({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
  // apply_operation_rgb(image, grayscale);
  apply_operation_rgb(image, isolate_green);
  image.save_to_file("output.png");

  for (unsigned int row = 1; row < image.get_height() - 1; ++row)
  {
    for (unsigned int column = 1; column < image.get_width() - 1; ++column)
    {
      unsigned char r, g, b;
      image.get_pixel(column, row, r, g, b);
      std::cout << "\033[38;2;" << (short)r << ";" << (short)g << ";" << (short)b << "m▓";
    }
    std::cout << std::endl;
  } 

  return 0;
}
