#include "linMap.h"

LinMap::LinMap() {}

LinMap::~LinMap() {}

float LinMap::linMap(float input, int x1, int x2, float min, float max)
{
  // STARTING AT A X VALUE
    float value = (min * (x2 - input) + max * (input - x1)) / (x2 - x1);
    return value;
}
