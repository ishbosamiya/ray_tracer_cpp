#ifndef PERLIN_H
#define PERLIN_H

#include <math.h>

#include "vec3.h"

extern float randomBetweenZeroOne();

float trilinearInterpolation(Vec3 c[2][2][2], float u, float v, float w);

class Perlin
{
    static Vec3 *ran_float;
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;

    public:
        float noise(const Vec3 &p) const;
        float turbulence(const Vec3 &p, int depth = 7) const;
};

static Vec3 *perlinGenerate();
void permute(int *p, int n);
static int *perlinGeneratePerm();

#endif // PERLIN_H
