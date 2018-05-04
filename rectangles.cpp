#include "rectangles.h"

//XY_Rectangle
bool XY_Rect::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    float t= (k - ray.originVector().z()) / ray.directionVector().z();

    if(t < t_min || t > t_max) {
        return false;
    }

    float x = ray.originVector().x() + t * ray.directionVector().x();
    float y = ray.originVector().y() + t * ray.directionVector().y();
    if(x < x0 || x > x1 || y < y0 || y > y1) {
        return false;
    }
    record.uv = Vec3((x - x0)/(x1 - x0), (y - y0)/(y1 - y0), 0.0);
    record.t = t;
    record.material_pointer = material;
    record.point = ray.pointAtParameter(t);
    record.normal = Vec3(0.0, 0.0, 1.0);
    return true;
}

bool XY_Rect::boundingBox(float time0, float time1, AABB &box) const {
    box = AABB(Vec3(x0, y0, k - 0.0001), Vec3(x1, y1, k + 0.0001));
    return true;
}
