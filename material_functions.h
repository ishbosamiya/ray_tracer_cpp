#ifndef MATERIAL_FUNTIONS_H
#define MATERIAL_FUNTIONS_H

#include "vec3.h"
#include "ray.h"

Vec3 reflect(Vec3 incident, Vec3 normal);
bool refract(Vec3 incident, Vec3 normal, float refractive_index, Vec3 &refracted);
float schlick(float cosine, float refractive_index);

#endif // MATERIAL_FUNTIONS_H
