#include "material_functions.h"

Vec3 reflect(const Hit_Record &record) {
    Vec3 incident = record.ray.directionVector().normalized();
    Vec3 normal = record.normal;
    return incident - normal*2*incident.dot(normal);
}

bool refract(const Hit_Record &record, float refractive_index, Vec3 &refracted) {
    Vec3 incident_normalized = record.ray.directionVector().normalized();
    Vec3 normal = record.normal;
    float dt = incident_normalized.dot(normal);

    if(dt > 0) {
        normal *= -1.0;
    }

    float discriminant = 1.0 - refractive_index*refractive_index*(1.0 - dt*dt);
    if(discriminant > 0) {
        refracted = (incident_normalized - normal * dt)*refractive_index - normal*sqrt(discriminant);
        return true;
    }
    else {
        return false;
    }
}

float schlick(float cosine, float refractive_index) {
//    float r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
//    r0 = r0*r0;
//    return r0 + (1.0-r0)*pow((1.0 - cosine), 5);
    float c = fabs(cosine);
    float g= refractive_index * refractive_index - 1.0 + c * c;
    float result;

    if(g > 0.0) {
        g = sqrt(g);
        float a = (g - c) / (g + c);
        float b = (c * (g + c) - 1.0)/ (c * (g - c) + 1.0);
        result = 0.5 * a * a * (1.0 + b * b);
    }
    else {
        result = 1.0;
    }
    return result;
}

float fresnelDielectric(float refractive_index, const Hit_Record &record) {
    float cosine = record.ray.directionVector().normalized().dot(record.normal);
    if(cosine > 0.0) {
        cosine *= refractive_index;
    }
    else {
        cosine *= -1.0;
    }
    return schlick(cosine, refractive_index);
}
