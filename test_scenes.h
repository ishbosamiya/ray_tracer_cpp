#ifndef TEST_SCENES_H
#define TEST_SCENES_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "texture.h"
#include "rectangles.h"
#include "sphere.h"

Hitable **simpleLight() {
    Texture *perlin_texture = new Noise_Texture(4);
    Hitable **list = new Hitable*[4];
    list[0] = new Sphere(Vec3(0.0, -1000.0, 0.0), 1000.0, new Lambertian(perlin_texture));
    list[1] = new Sphere(Vec3(0.0, 2.0, 0.0), 2.0, new Lambertian(perlin_texture));
    list[2] = new Sphere(Vec3(0.0, 7.0, 0.0), 2.0, new Diffuse_Light(new Constant_Texture(Vec3(0.0, 0.0, 0.0))));
    list[3] = new XY_Rect(3.0, 5.0, 1.0, 3.0, -2.0, new Diffuse_Light(new Constant_Texture(Vec3(4.0, 4.0, 4.0))));
    return list;
}

#endif // TEST_SCENES_H
