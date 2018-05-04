#ifndef HITABLE_H
#define HITABLE_H

#define M_PI 3.141592653

#include <math.h>
#include <float.h>

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

class Translate: public Hitable {
    Hitable *ptr;
    Vec3 offset;

    public:
        Translate(Hitable *ptr, Vec3 offset) {
            this->ptr = ptr;
            this->offset = offset;
        }

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
            Ray moved_ray(ray.originVector() - offset, ray.directionVector());
            if(ptr->hit(moved_ray, t_min, t_max, record)) {
                record.point += offset;
                return true;
            }
            else {
                return false;
            }
        }
        virtual bool boundingBox(float time0, float time1, AABB &box) const {
            if(ptr->boundingBox(time0, time1, box)) {
                box = AABB(box.min() + offset, box.max() + offset);
                return true;
            }
            else {
                return false;
            }
        }
};

class Rotate_Y: public Hitable {
    Hitable *ptr;
    float sin_theta;
    float cos_theta;
    bool has_box;
    AABB box;

    public:
        Rotate_Y(Hitable *ptr, float angle) {
            this->ptr = ptr;
            float radians = (M_PI/180.0)*angle;
            sin_theta = sin(radians);
            cos_theta = cos(radians);
            has_box = ptr->boundingBox(0.0, 1.0, this->box);
            Vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
            Vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    for(int k = 0; k < 2; k++) {
                        float x = i * box.max().x() + (1.0 - i)*box.min().x();
                        float y = j * box.max().y() + (1.0 - j)*box.min().y();
                        float z = k * box.max().z() + (1.0 - k)*box.min().z();
                        float newx = cos_theta*x + sin_theta*z;
                        float newz = -sin_theta*x + cos_theta*z;
                        Vec3 tester(newx, y, newz);
                        for(int c = 0; c < 3; c++) {
                            if(tester[c] > max[c]) {
                                max[c] = tester[c];
                            }
                            if(tester[c] < min[c]) {
                                min[c] = tester[c];
                            }
                        }
                    }
                }
            }

            this->box = AABB(min, max);
        }

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
            Vec3 origin = ray.originVector();
            Vec3 direction = ray.directionVector();
            origin[0] = cos_theta*origin[0] - sin_theta*origin[2];
            origin[2] = sin_theta*origin[0] + cos_theta*origin[2];
            direction[0] = cos_theta*direction[0] - sin_theta*direction[2];
            direction[2] = sin_theta*direction[0] + cos_theta*direction[2];
            Ray rotated_ray(origin, direction);
            if(ptr->hit(rotated_ray, t_min, t_max, record)) {
                Vec3 point = record.point;
                Vec3 normal = record.normal;
                point[0] = cos_theta*point[0] + sin_theta*point[2];
                point[2] = -sin_theta*point[0] + cos_theta*point[2];
                normal[0] = cos_theta*normal[0] + sin_theta*normal[2];
                normal[2] = -sin_theta*normal[0] + cos_theta*normal[2];
                record.point = point;
                record.normal = normal;
                return true;
            }
            else {
                return false;
            }
        }

        virtual bool boundingBox(float time0, float time1, AABB &box) const {
            box = this->box;
            return has_box;
        }
};

#endif // HITABLE_H
