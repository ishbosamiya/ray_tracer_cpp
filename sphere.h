#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "aabb.h"

void getSphereUV(const Vec3 &point, Vec3 &uv);

class Sphere: public Hitable {
    Vec3 center;
    float radius;
    Material *material;

    public:
        Sphere();
        Sphere(Vec3 center, float radius, Material *material);

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;
        virtual bool boundingBox(float time0, float time1, AABB &box) const;

        virtual ~Sphere();
};

#endif // SPHERE_H
