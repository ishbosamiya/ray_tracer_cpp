#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

struct Hit_Record {
    float t;
    Vec3 point;
    Vec3 normal;
};

class Hitable
{
    public:
        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const = 0;
};

#endif // HITABLE_H
