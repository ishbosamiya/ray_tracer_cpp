#include "sphere.h"

Sphere::Sphere() {
    material = nullptr;
}

Sphere::Sphere(Vec3 center, float radius, Material *material) {
    this->center = center;
    this->radius = radius;
    this->material = material;
}

bool Sphere::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    Vec3 oc = ray.originVector() - center;
    float a = ray.directionVector().dot(ray.directionVector());
    float b = 2.0 * oc.dot(ray.directionVector());
    float c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    float discriminant_sqrt = sqrt(discriminant);
    if(discriminant > 0) {
        float temp = (-b - discriminant_sqrt)/(2.0*a);
        if(temp < t_max && temp > t_min) {
            record.t = temp;
            record.point = ray.pointAtParameter(record.t);
            record.normal = (record.point - center) / radius;
            record.material_pointer = material;
            return true;
        }
        temp = (-b + discriminant_sqrt)/(2.0*a);
        if(temp < t_max && temp > t_min) {
            record.t = temp;
            record.point = ray.pointAtParameter(record.t);
            record.normal = (record.point - center) / radius;
            record.material_pointer = material;
            return true;
        }
    }
    return false;
}

Sphere::~Sphere() {
    delete material;
}
