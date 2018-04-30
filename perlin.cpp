#include "perlin.h"

float Perlin::noise(const Vec3 &p) const {
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());

    u = u*u*(3-2*u);
    v = v*v*(3-2*v);
    w = w*w*(3-2*w);

    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());
    float c[2][2][2];
    for(int di = 0; di < 2; di++) {
        for(int dj = 0; dj < 2; dj++) {
            for(int dk = 0; dk < 2; dk++) {
                c[di][dj][dk] = ran_float[perm_x[(i+di) & 255] ^
                                            perm_y[(j+dj) & 255] ^
                                            perm_z[(k+dk) & 255]];
            }
        }
    }

    return trilinearInterpolation(c, u, v, w);
}

float trilinearInterpolation(float c[2][2][2], float u, float v, float w) {
    float accum = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                accum += (i*u + (1 - i)*(1 - u))*
                            (j*v + (1 - j)*(1 - v))*
                            (k*w + (1 - k)*(1 - w))*c[i][j][k];
            }
        }
    }
    return accum;
}

static float *perlinGenerate() {
    float *p = new float[256];
    for(int i = 0; i < 256; i++) {
        p[i] = randomBetweenZeroOne();
    }
    return p;
}

void permute(int *p, int n) {
    for(int i = n - 1; i > 0; i--) {
        int target = (int)(randomBetweenZeroOne() * (i + 1));
        int temp = p[i];
        p[i] = p[target];
        p[target] = temp;
    }
    return;
}

static int *perlinGeneratePerm() {
    int *p = new int[256];
    for(int i = 0; i < 256; i++) {
        p[i] = i;
    }
    permute(p, 256);
    return p;
}

float *Perlin::ran_float = perlinGenerate();
int *Perlin::perm_x = perlinGeneratePerm();
int *Perlin::perm_y = perlinGeneratePerm();
int *Perlin::perm_z = perlinGeneratePerm();
