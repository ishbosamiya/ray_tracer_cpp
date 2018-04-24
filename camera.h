#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera
{
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
    public:
        Camera(float vertical_fov, float aspect_ratio);

        Ray getRay(float u, float v);

        virtual ~Camera();
};

#endif // CAMERA_H
