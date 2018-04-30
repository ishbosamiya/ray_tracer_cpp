#ifndef PERLIN_H
#define PERLIN_H

#include <math.h>

#include "vec3.h"

extern float randomBetweenZeroOne();

float trilinearInterpolation(float c[2][2][2], float u, float v, float w);

class Perlin
{
    static float *ran_float;
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;

    public:
        float noise(const Vec3 &p) const;
};

static float *perlinGenerate();
void permute(int *p, int n);
static int *perlinGeneratePerm();

#endif // PERLIN_H
