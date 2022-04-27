#include "simplex.h"

#define F2 0.366025403f // (sqrt(3.0) - 1.0) / 2.0
#define G2 0.211324865f // (3.0 - sqrt(3.0)) / 6.0

const int permutation[] = {
    151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
    140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
    247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
     57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
     74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
     60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
     65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
    200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
     52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
    207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
    119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
    129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
    218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
     81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
    184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
    222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
};

static int fastfloor(float x)
{
    int xi = (int) x;
    return x < xi ? xi - 1 : xi;
}

static int hash(int seed, int i)
{
    return permutation[(i + seed) & 255];
}

static float grad1d(int hash, float x)
{
    int h = hash & 15;
    float g = 1.0f + (h & 7);
    if ((h & 8) != 0) g = -g;
    return g * x;
}

static float grad2d(int hash, float x, float y)
{
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) != 0 ? -u : u) + ((h & 2) != 0 ? -2.0f * v : 2.0f * v);
}

float simplex_noise1d(float x, int seed)
{
    int i0 = fastfloor(x);
    int i1 = i0 + 1;

    float x0 = x - i0;
    float x1 = x0 - 1.0f;

    float t0 = 1.0f - x0 * x0;
    float t1 = 1.0f - x1 * x1;
    t0 *= t0;
    t1 *= t1;

    float n0 = t0 * t0 * grad1d(hash(seed, i0), x0);
    float n1 = t1 * t1 * grad1d(hash(seed, i1), x1);

    return 0.395f * (n0 + n1);
}

float simplex_noise2d(float x, float y, int seed)
{
    float n0, n1, n2;

    float s = (x + y) * F2;
    int i = fastfloor(x + s);
    int j = fastfloor(y + s);
    float t = (i + j) * G2;

    float x0 = i - t;
    float y0 = j - t;
    x0 = x - x0;
    y0 = y - y0;

    int i1 = x0 > y0 ? 1 : 0;
    int j1 = x0 > y0 ? 0 : 1;

    float x1 = x0 - i1 + G2;
    float y1 = y0 - j1 + G2;
    float x2 = x0 - 1.0f + 2.0f * G2;
    float y2 = y0 - 1.0f + 2.0f * G2;

    int g0 = hash(seed, i + hash(seed, j));
    int g1 = hash(seed, i + i1 + hash(seed, j + j1));
    int g2 = hash(seed, i + 1 + hash(seed, j + 1));

    float t0 = 0.5f - x0 * x0 - y0 * y0;
    if (t0 < 0.0f) {
        n0 = 0.0f;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * grad2d(g0, x0, y0);
    }

    float t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 < 0.0f) {
        n1 = 0.0f;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * grad2d(g1, x1, y1);
    }

    float t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t2 < 0.0f) {
        n2 = 0.0f;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * grad2d(g2, x2, y2);
    }

    return 45.23065f * (n0 + n1 + n2);
}
