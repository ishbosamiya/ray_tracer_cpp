#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "texture.h"
#include "material_functions.h"

extern float randomBetweenZeroOne();
extern Vec3 randomInUnitSphere();

class Material {
    public:
        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const = 0;
};

//The Materials

class Lambertian: public Material {
    Texture *albedo;

    public:
        Lambertian(Texture *albedo) { this->albedo = albedo;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 target = record.point + record.normal + randomInUnitSphere();
            scattered = Ray(record.point, target-record.point);
            attenuation = albedo->value(Vec3(0,0,0), record);
            return true;
        }
};

class Metal: public Material {
    Vec3 albedo;
    float fuzz;

    public:
        Metal(Vec3 albedo, float fuzz) { this->albedo = albedo; this->fuzz = fuzz<0.999?fuzz:0.999;}

        virtual bool scatter(Ray &ray_in, Hit_Record &record, Vec3 &attenuation, Ray &scattered) const {
            Vec3 reflected = reflect(record);
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
            Vec3 reflected = reflect(record);
            float relative_ri;
            attenuation = Vec3(1.0, 1.0, 1.0);
            Vec3 refracted;
            float reflection_probability;
            float cosine;

            if(refract(record, relative_ri, refracted)) {
                reflection_probability = fresnelDielectric(refractive_index, record);
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

#endif // MATERIAL_H
