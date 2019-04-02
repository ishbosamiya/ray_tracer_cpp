#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include <math.h>
#include <float.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "texture.h"
#include "aabb.h"

extern float randomBetweenZeroOne();

class Constant_Medium: public Hitable
{
    Hitable *boundary;
    float density;
    Material *phase_function;

    public:
        Constant_Medium(Hitable *boundary, float density, Texture *albedo) {
            this->boundary = boundary;
            this->density = density;
            phase_function = new Isotropic_Material(albedo);
        }

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;
        virtual bool boundingBox(float time0, float time1, AABB &box) const;
};

#endif // CONSTANT_MEDIUM_H
