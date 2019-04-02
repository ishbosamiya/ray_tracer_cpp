#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b;}
inline float ffmax(float a, float b) { return a > b ? a : b;}

class AABB
{
    Vec3 m_min;
    Vec3 m_max;

    public:
        AABB();
        AABB(Vec3 min, Vec3 max);

        Vec3 min() const {return m_min;}
        Vec3 max() const {return m_max;}

        bool hit(Ray &ray, float &t_min, float &t_max) const;

        virtual ~AABB();
};

AABB surroundingBox(AABB box0, AABB box1);

#endif // AABB_H
