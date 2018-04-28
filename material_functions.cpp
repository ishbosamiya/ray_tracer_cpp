#include "material_functions.h"

Vec3 reflect(Vec3 incident, Vec3 normal) {
    return incident - normal*2*incident.dot(normal);
}

bool refract(Vec3 incident, Vec3 normal, float refractive_index, Vec3 &refracted) {
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

float schlick(float cosine, float refractive_index) {
    float r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
    r0 = r0*r0;
    return r0 + (1.0-r0)*pow((1.0 - cosine), 5);
}
