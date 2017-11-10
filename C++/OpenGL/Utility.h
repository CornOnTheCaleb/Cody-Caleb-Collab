#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <ctime>

void rand_seed ();

long rand_in_range (const long lowerLimit, const long upperLimit);

float rand_in_range (const float lowerLimit, const float upperLimit);

bool rand_bool ();

#endif
