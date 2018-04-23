#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

extern Vec3 randomInUnitSphere();

class Material {
    public:
        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const = 0;

    protected:
        Vec3 reflect(Vec3 incident, Vec3 normal) const {
            return incident - normal*2*incident.dot(normal);
        }
};

//The Materials

class Lambertian: public Material {
    Vec3 albedo;

    public:
        Lambertian(Vec3 albedo) { this->albedo = albedo;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 target = record.point + record.normal + randomInUnitSphere();
            scattered = Ray(record.point, target-record.point);
            attenuation = albedo;
            return true;
        }
};

class Metal: public Material {
    Vec3 albedo;

    public:
        Metal(Vec3 albedo) { this->albedo = albedo;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 ray_in_direction_normalized = ray_in.directionVector().normalized();
            Vec3 reflected = reflect(ray_in.directionVector().normalized(), record.normal);
            scattered = Ray(record.point, reflected);
            attenuation = albedo;
            return (scattered.directionVector().dot(record.normal) > 0);
        }
};

#endif // MATERIAL_H
