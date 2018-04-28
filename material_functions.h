#ifndef MATERIAL_FUNTIONS_H
#define MATERIAL_FUNTIONS_H

#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

Vec3 reflect(const Hit_Record &record);
bool refract(const Hit_Record &record, float refractive_index, Vec3 &refracted);
float schlick(float cosine, float refractive_index);
float fresnelDielectric(float refractive_index, Hit_Record &record);

#endif // MATERIAL_FUNTIONS_H
