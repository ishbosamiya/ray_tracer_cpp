#include "camera.h"

#define PI 3.141592653

Camera::Camera(float vertical_fov, float aspect_ratio) {
    float theta = vertical_fov * PI / 180.0;
    float half_height = tan(theta/2.0);
    float half_width = aspect_ratio * half_height;

    lower_left_corner = Vec3(-half_width, -half_height, -1.0);
    horizontal = Vec3(2.0*half_width, 0.0, 0.0);
    vertical = Vec3(0.0, 2.0 * half_height, 0.0);
    origin = Vec3(0.0, 0.0, 0.0);
}

Ray Camera::getRay(float u, float v) {
    return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);
}

Camera::~Camera()
{
    //dtor
}
