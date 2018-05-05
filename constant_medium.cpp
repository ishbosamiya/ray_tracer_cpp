#include "constant_medium.h"

bool Constant_Medium::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    bool db = randomBetweenZeroOne() < 0.00001;
    db = false;
    Hit_Record record1, record2;
    if(boundary->hit(ray, -FLT_MAX, FLT_MAX, record1)) {
        if(boundary->hit(ray, record1.t + 0.0001, FLT_MAX, record2)) {
            if(record1.t < t_min) {
                record1.t = t_min;
            }
            if(record2.t > t_max) {
                record2.t = t_max;
            }
            if(record1.t >= record2.t) {
                return false;
            }
            if(record1.t < 0) {
                record1.t = 0;
            }
            float distance_inside_boundary = (record2.t - record1.t)*ray.directionVector().length();
            float hit_distance = -(1.0/density)*log(randomBetweenZeroOne());
            if(hit_distance < distance_inside_boundary) {
                record.t = record1.t + hit_distance / ray.directionVector().length();
                record.point = ray.pointAtParameter(record.t);
                record.normal = Vec3(1.0, 0.0, 0.0);
                record.material_pointer = phase_function;
                return true;
            }
        }
    }
    return false;
}

bool Constant_Medium::boundingBox(float time0, float time1, AABB &box) const {
    return boundary->boundingBox(time0, time1, box);
}
