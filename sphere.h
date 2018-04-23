#ifndef SPHERE_H
#define SPHERE_H


#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"

class Sphere: public Hitable {
    Vec3 center;
    float radius;
    Material *material;

    public:
        Sphere();
        Sphere(Vec3 center, float radius, Material *material);

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;

        virtual ~Sphere();
};

#endif // SPHERE_H
