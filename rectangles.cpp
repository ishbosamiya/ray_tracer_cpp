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

//XZ_Rectangle
bool XZ_Rect::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    float t= (k - ray.originVector().y()) / ray.directionVector().y();

    if(t < t_min || t > t_max) {
        return false;
    }

    float x = ray.originVector().x() + t * ray.directionVector().x();
    float z = ray.originVector().z() + t * ray.directionVector().z();
    if(x < x0 || x > x1 || z < z0 || z > z1) {
        return false;
    }
    record.uv = Vec3((x - x0)/(x1 - x0), (z - z0)/(z1 - z0), 0.0);
    record.t = t;
    record.material_pointer = material;
    record.point = ray.pointAtParameter(t);
    record.normal = Vec3(0.0, 1.0, 0.0);
    return true;
}

bool XZ_Rect::boundingBox(float time0, float time1, AABB &box) const {
    box = AABB(Vec3(x0, k - 0.0001, z0), Vec3(x1, k + 0.0001, z1));
    return true;
}


//YZ_Rectangle
bool YZ_Rect::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    float t= (k - ray.originVector().x()) / ray.directionVector().x();

    if(t < t_min || t > t_max) {
        return false;
    }

    float y = ray.originVector().y() + t * ray.directionVector().y();
    float z = ray.originVector().z() + t * ray.directionVector().z();
    if(y < y0 || y > y1 || z < z0 || z > z1) {
        return false;
    }
    record.uv = Vec3((y - y0)/(y1 - y0), (z - z0)/(z1 - z0), 0.0);
    record.t = t;
    record.material_pointer = material;
    record.point = ray.pointAtParameter(t);
    record.normal = Vec3(1.0, 0.0, 0.0);
    return true;
}

bool YZ_Rect::boundingBox(float time0, float time1, AABB &box) const {
    box = AABB(Vec3(k - 0.0001, y0, z0), Vec3(k + 0.0001, y1, z1));
    return true;
}
