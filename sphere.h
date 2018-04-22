#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class Sphere: public Hitable
{
    Vec3 center;
    float radius;
    public:
        Sphere();
        Sphere(Vec3 center, float radius);

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;

        virtual ~Sphere();
};

#endif // SPHERE_H
