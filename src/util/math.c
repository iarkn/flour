#include "util/math.h"

float clamp(float val, float min, float max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

float max(float a, float b)
{
    return a > b ? a : b;
}
