#include "camera.h"

#define PI 3.141592653

Camera::Camera(Vec3 look_from, Vec3 look_at, Vec3 vertical_up, float vertical_fov, float aspect_ratio) {
    Vec3 u, v, w;
    float theta = vertical_fov * PI / 180.0;
    float half_height = tan(theta/2.0);
    float half_width = aspect_ratio * half_height;

    origin = look_from;
    w = (look_from - look_at).normalized();
    u = vertical_up.cross(w).normalized();
    v = w.cross(u);

    lower_left_corner = origin - u*half_width - v*half_height - w;
    horizontal = u*2.0*half_width;
    vertical = v*2.0*half_height;
}

Ray Camera::getRay(float u, float v) {
    return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);
}

Camera::~Camera()
{
    //dtor
}
