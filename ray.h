#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    Vec3 origin;
    Vec3 direction;

    public:
        Ray();
        Ray(const Vec3 &origin, const Vec3 &direction);

        inline Vec3 originVector() const { return origin;}
        inline Vec3 directionVector() const { return direction;}
        inline Vec3 pointAtParameter(float t) const { return origin + (direction * t);}

        virtual ~Ray();
};

#endif // RAY_H
