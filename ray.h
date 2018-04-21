#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
    Vec3 origin;
    Vec3 direction;

    public:
        Ray();
        Ray(const Vec3 &origin, const Vec3 &direction);

        inline Vec3 originVector() { return origin;}
        inline Vec3 directionVector() { return direction;}
        inline Vec3 pointAtParameter(float t) { return origin + (direction * t);}

        virtual ~Ray();
};

#endif // RAY_H
