#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera
{
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
    public:
        Camera();

        Ray getRay(float u, float v);

        virtual ~Camera();
};

#endif // CAMERA_H
