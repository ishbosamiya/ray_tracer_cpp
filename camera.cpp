#include "camera.h"

Camera::Camera() {
    extern const float width;
    extern const float height;

    lower_left_corner = Vec3(-width/height*1.000001, -1, -1.4);
    horizontal = Vec3(width*2.0/height, 0.0, 0.0);
    vertical = Vec3(0.0, 2.0, 0.0);
    origin = Vec3(0.0, 0.0, 0.0);
}

Ray Camera::getRay(float u, float v) {
    return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);
}

Camera::~Camera()
{
    //dtor
}
