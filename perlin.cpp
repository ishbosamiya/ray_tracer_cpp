#include "perlin.h"

float Perlin::noise(const Vec3 &p) const {
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());

    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());
    Vec3 c[2][2][2];
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

float Perlin::turbulence(const Vec3 &p, int depth) const {
    float accum = 0;
    Vec3 temp_p = p;
    float weight = 1.0;
    for(int i = 0; i < depth; i++) {
        accum += weight*noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }
    return fabs(accum);
}

float trilinearInterpolation(Vec3 c[2][2][2], float u, float v, float w) {
    float uu = u*u*(3.0-2.0*u);
    float vv = v*v*(3.0-2.0*v);
    float ww = w*w*(3.0-2.0*w);
    float accum = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                Vec3 weight_v(u-i, v-j, w-k);
                accum += (i*uu + (1.0 - i)*(1.0 - uu))*
                            (j*vv + (1.0 - j)*(1.0 - vv))*
                            (k*ww + (1.0 - k)*(1.0 - ww))*(weight_v.dot(c[i][j][k]));
            }
        }
    }
    return accum;
}

static Vec3 *perlinGenerate() {
    Vec3 *p = new Vec3[256];
    for(int i = 0; i < 256; i++) {
        p[i] = Vec3(-1.0 + 2.0*randomBetweenZeroOne(),
                    -1.0 + 2.0*randomBetweenZeroOne(),
                    -1.0 + 2.0*randomBetweenZeroOne()).normalized();
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

Vec3 *Perlin::ran_float = perlinGenerate();
int *Perlin::perm_x = perlinGeneratePerm();
int *Perlin::perm_y = perlinGeneratePerm();
int *Perlin::perm_z = perlinGeneratePerm();
