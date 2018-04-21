#include "ray.h"

Ray::Ray() {
    origin = Vec3();
    direction = Vec3();
}

Ray::Ray(const Vec3 &origin, const Vec3 &direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::~Ray()
{
    //dtor
}
