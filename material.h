#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

extern float randomBetweenZeroOne();
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

        float schlick(float cosine, float refractive_index) const {
            float r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
            r0 = r0*r0;
            return r0 + (1.0-r0)*pow((1.0 - cosine), 5);
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
        Dielectric(float refractive_index, float fuzz = 0.0) {
            this->refractive_index = refractive_index;
            this->fuzz = fuzz < 0.999 ? fuzz : 0.999;
        }

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 outward_normal;
            Vec3 reflected = reflect(ray_in.directionVector(), record.normal);
            float relative_ri;
            attenuation = Vec3(1.0, 1.0, 1.0);
            Vec3 refracted;
            float reflection_probability;
            float cosine;

            if(ray_in.directionVector().dot(record.normal) > 0) {
                outward_normal = Vec3(0.0, 0.0, 0.0) - record.normal;
                relative_ri = refractive_index;
                cosine = refractive_index * ray_in.directionVector().dot(record.normal) / ray_in.directionVector().length();
            }
            else {
                outward_normal = record.normal;
                relative_ri = 1.0/refractive_index;
                cosine = -ray_in.directionVector().dot(record.normal) / ray_in.directionVector().length();
            }

            if(refract(ray_in.directionVector(), outward_normal, relative_ri, refracted)) {
                reflection_probability = schlick(cosine, refractive_index);
            }
            else {
                reflection_probability = 1.0;
            }

            if(randomBetweenZeroOne() < reflection_probability) {
                scattered = Ray(record.point, reflected + (randomInUnitSphere()*fuzz));
            }
            else {
                scattered = Ray(record.point, refracted + (randomInUnitSphere()*fuzz));
            }

            return true;
        }
};

class Fresnel_Material: public Material {
    float refractive_index;

    public:
        Fresnel_Material(float refractive_index) { this->refractive_index = refractive_index;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            float cosine;
            float reflection_probability;
            float relative_ri;
            if(ray_in.directionVector().dot(record.normal) > 0) {
                relative_ri = refractive_index;
                cosine = refractive_index * ray_in.directionVector().dot(record.normal) / ray_in.directionVector().length();
            }
            else {
                relative_ri = 1.0/refractive_index;
                cosine = -ray_in.directionVector().dot(record.normal) / ray_in.directionVector().length();
            }
            reflection_probability = schlick(cosine, relative_ri);

            Vec3 target = record.point + record.normal + randomInUnitSphere();
            scattered = Ray(record.point, target-record.point);
            attenuation = Vec3(reflection_probability, reflection_probability, reflection_probability);
            return true;
        }
};

#endif // MATERIAL_H
