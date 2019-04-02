#include "aabb.h"

AABB::AABB() {
    //ctor
}

AABB::AABB(Vec3 min, Vec3 max) {
    this->m_min = min;
    this->m_max = max;
}

bool AABB::hit(Ray &ray, float &t_min, float &t_max) const {
    for(int i = 0; i < 3; i++) {
        float inv_ray_direction = 1.0/ray.directionVector()[i];
        float t0 = ffmin((min()[i] - ray.originVector()[i])*inv_ray_direction,
                         (max()[i] - ray.originVector()[i])*inv_ray_direction);
        float t1 = ffmax((min()[i] - ray.originVector()[i])*inv_ray_direction,
                         (max()[i] - ray.originVector()[i])*inv_ray_direction);
        t_min = ffmax(t0, t_min);
        t_max = ffmin(t1, t_max);
        if(t_max <= t_min) {
            return false;
        }
    }
    return true;
}

AABB::~AABB() {
    //dtor
}

AABB surroundingBox(AABB box0, AABB box1) {
    Vec3 small(ffmin(box0.min().x(), box1.min().x()),
               ffmin(box0.min().y(), box1.min().y()),
               ffmin(box0.min().z(), box1.min().z()));
    Vec3 big(ffmax(box0.max().x(), box1.max().x()),
             ffmax(box0.max().y(), box1.max().y()),
             ffmax(box0.max().z(), box1.max().z()));
    return AABB(small, big);
}
