#include "Utility.h"

void rand_seed ()
{
  srand((unsigned int)time(NULL));
}

long rand_in_range (const long lowerLimit, const long upperLimit)
{
  return (rand() % (upperLimit - lowerLimit + 1) + lowerLimit);
}

float rand_in_range (const float lowerLimit, const float upperLimit)
{
  return static_cast<float>(rand()) / (static_cast <float> (RAND_MAX / (upperLimit - lowerLimit))) + lowerLimit;
}

bool rand_bool ()
{
  return (rand() % 2);
}
