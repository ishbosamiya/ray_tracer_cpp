#ifndef RECTANGLES_H
#define RECTANGLES_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "aabb.h"

class XY_Rect: public Hitable {
    float x0, x1, y0, y1, k;
    Material *material;

    public:
        XY_Rect() {}
        XY_Rect(float x0, float x1, float y0, float y1, float k, Material *material) {
            this->x0 = x0;
            this->x1 = x1;
            this->y0 = y0;
            this->y1 = y1;
            this->k = k;
            this->material = material;
        }

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;
        virtual bool boundingBox(float time0, float time1, AABB &box) const;
};

#endif // RECTANGLES_H
