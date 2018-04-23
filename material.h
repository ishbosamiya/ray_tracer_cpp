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

        bool refract(Vec3 incident, Vec3 normal, float refractive_index, Vec3 &refracted) const {
            Vec3 incident_normalized = incident.normalized();
            float dt = incident_normalized.dot(normal);
            float discriminant = 1.0 - refractive_index*refractive_index*(1.0 - dt*dt);
            if(discriminant > 0) {
                refracted = (incident_normalized - normal * dt)*refractive_index - normal*sqrt(discriminant);
                return true;
            }
            else {
                return false;
            }
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
    float fuzz;

    public:
        Metal(Vec3 albedo, float fuzz) { this->albedo = albedo; this->fuzz = fuzz<0.999?fuzz:0.999;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 reflected = reflect(ray_in.directionVector().normalized(), record.normal);
            scattered = Ray(record.point, reflected + (randomInUnitSphere()*fuzz));
            attenuation = albedo;
            return (scattered.directionVector().dot(record.normal) > 0);
        }
};

class Dielectric: public Material {
    float refractive_index;
    float fuzz;

    public:
        Dielectric(float refractive_index, float fuzz = 0.0) { this->refractive_index = refractive_index; this->fuzz = fuzz;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 outward_normal;
            Vec3 reflected = reflect(ray_in.directionVector(), record.normal);
            float relative_ri;
            attenuation = Vec3(1.0, 1.0, 1.0);
            Vec3 refracted;

            if(ray_in.directionVector().dot(record.normal) > 0) {
                outward_normal = Vec3(0.0, 0.0, 0.0) - record.normal;
                relative_ri = refractive_index;
            }
            else {
                outward_normal = record.normal;
                relative_ri = 1.0/refractive_index;
            }

            if(refract(ray_in.directionVector(), outward_normal, relative_ri, refracted)) {
                scattered = Ray(record.point, refracted + (randomInUnitSphere()*fuzz));
            }
            else {
                scattered = Ray(record.point, refracted);
                return false;
            }
            return true;
        }
};

#endif // MATERIAL_H
