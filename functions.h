#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"

using namespace std;

extern const float multiplier;
extern const int width;
extern const int height;

int getIndex(int x, int y);
void writeToPPM(char *components, char *path);
Vec3 backgroundColor(Ray &ray, Hitable *world);
float hitSphere(Vec3 center, float radius, Ray ray);

int getIndex(int x, int y) {
    return (x + y * width) * 3;
}

void writeToPPM(char *components, char *path) {
    ofstream fout;
    fout.open(path);
    if(!fout.is_open()) {
        cout << "Couldn't Write PPM To File" << endl;
        return;
    }
    fout << "P3" << endl;
    fout << width << " " << height << endl;
    fout << "255" << endl;
    for(int y = height - 1; y >= 0; y--) {
        for(int x = 0; x < width; x++) {
            unsigned char r = components[getIndex(x, y) + 0];
            unsigned char g = components[getIndex(x, y) + 1];
            unsigned char b = components[getIndex(x, y) + 2];
            fout << (int)r << " " << (int)g << " " << (int)b << "\t";
        }
        fout << endl;
    }
}

Vec3 backgroundColor(Ray &ray, Hitable *world) {
    Hit_Record record;
    if(world->hit(ray, 0.0, 10000.0, record)) {
        return (record.normal + Vec3(1.0, 1.0, 1.0))*0.5;
    }
    else {
        Vec3 unit_direction = ray.directionVector().normalized();
        float t = (unit_direction.y() + 1.0)*0.5;
        return Vec3(1.0, 1.0, 1.0)*(1.0 - t) + Vec3(0.5, 0.7, 1.0)*t;
    }
}

float hitSphere(Vec3 center, float radius, Ray ray) {
    Vec3 oc = ray.originVector() - center;
    float a = ray.directionVector().dot(ray.directionVector());
    float b = 2.0 * oc.dot(ray.directionVector());
    float c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0) {
        return -1.0;
    }
    else {
        return ((-b - sqrt(discriminant)) / (2.0*a));
    }
}

#endif // FUNCTIONS_H
