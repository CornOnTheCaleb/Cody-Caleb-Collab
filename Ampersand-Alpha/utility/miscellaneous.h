#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

int clamp (const int value, const int min, const int max)
{
  return (value < min ? min : (value > max ? max : value));
}

#endif
