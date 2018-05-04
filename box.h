#ifndef BOX_H
#define BOX_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "aabb.h"
#include "bvh_node.h"
#include "rectangles.h"

class Box: public Hitable
{
    Vec3 pmin, pmax;
    Hitable *list_ptr;

    public:
        Box() {}
        Box(Vec3 pmin, Vec3 pmax, Material *material);
        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;
        virtual bool boundingBox(float time0, float time1, AABB &box) const;
};

#endif // BOX_H
