#ifndef HITABLE_H
#define HITABLE_H

#include "vec3.h"
#include "ray.h"
#include "aabb.h"

class Material;

struct Hit_Record {
    Ray ray;
    float t;
    Vec3 point;
    Vec3 normal;
    Vec3 uv;
    Material *material_pointer;
};

class Hitable {
    public:
        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const = 0;
        virtual bool boundingBox(float time0, float time1, AABB &box) const = 0;
};

class Flip_Normals: public Hitable {
    Hitable *ptr;
    public:
        Flip_Normals(Hitable *ptr) {
            this->ptr = ptr;
        }
        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
            if(ptr->hit(ray, t_min, t_max, record)) {
                record.normal = Vec3(0.0, 0.0, 0.0) - record.normal;
                return true;
            }
            else {
                return false;
            }
        }

        virtual bool boundingBox(float time0, float time1, AABB &box) const {
            return ptr->boundingBox(time0, time1, box);
        }
};

#endif // HITABLE_H
