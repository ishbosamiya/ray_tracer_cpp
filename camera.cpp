#include "camera.h"

#define PI 3.141592653

Camera::Camera(Vec3 look_from, Vec3 look_at, Vec3 vertical_up, float vertical_fov, float aspect_ratio, float aperture, float focal_length) {
    lens_radius = aperture * 0.5;
    float theta = vertical_fov * PI / 180.0;
    float half_height = tan(theta/2.0);
    float half_width = aspect_ratio * half_height;

    origin = look_from;
    w = (look_from - look_at).normalized();
    u = vertical_up.cross(w).normalized();
    v = w.cross(u);

    lower_left_corner = origin - u*half_width*focal_length - v*half_height*focal_length - w*focal_length;
    horizontal = u*2.0*half_width*focal_length;
    vertical = v*2.0*half_height*focal_length;
}

Ray Camera::getRay(float u, float v) {
    Vec3 rd = randomInUnitDisk() * lens_radius;
    Vec3 offset = (this->u * rd.x()) + (this->v * rd.y());

    return Ray(origin + offset, lower_left_corner + horizontal*u + vertical*v - origin - offset);
}

Camera::~Camera()
{
    //dtor
}
