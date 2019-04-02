#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

extern float randomBetweenZeroOne();
extern Vec3 randomInUnitDisk();

class Camera
{
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
    Vec3 u, v, w;
    float lens_radius;

    public:
        Camera(Vec3 look_from, Vec3 look_at, Vec3 vertical_up, float vertical_fov, float aspect_ratio, float aperture, float focal_length);

        Ray getRay(float u, float v);

        virtual ~Camera();
};

#endif // CAMERA_H
