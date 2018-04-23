#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>

#include "hitable.h"
#include "sphere.h"
#include "material.h"
#include "hitable_list.h"
#include "camera.h"
#include "functions.h"

using namespace std;

const float multiplier = 0.2;
const int width = 1280 * multiplier;
const int height = 720 * multiplier;
const int no_of_samples = 5;
const int total_samples = no_of_samples * width * height;


int main() {
    srand(time(0));

    char *pixels = new char[width * height * 3];

    Hitable *list[4];
    list[0] = new Sphere(Vec3(0.0, 0.0, -1.0), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec3(0.0, -100.5, -1.0), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vec3(1.0, 0.0, -1.0), 0.5, new Metal(Vec3(0.3, 0.9, 0.3), 0.6));
    list[3] = new Sphere(Vec3(-1.0, 0.0, -1.0), 0.5, new Dielectric(1.5, 0.2));
    Hitable *world = new Hitable_List(list, 4);

    Camera camera;

    for(int y = height - 1; y >= 0; y--) {
        for(int x = 0; x < width; x++) {
            Vec3 color(0.0, 0.0, 0.0);
            for(int s = 0; s < no_of_samples; s++) {
                float u = ((float)x + randomBetweenZeroOne())/ (float)width;
                float v = ((float)y + randomBetweenZeroOne())/ (float)height;

                Ray ray = camera.getRay(u, v);

                Vec3 p = ray.pointAtParameter(2.0);

                color += backgroundColor(ray, world, 0);

                percentageCompleted(); //gives report of how much of the ray tracing is done
            }

            color /= (float)no_of_samples;

            color = Vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2])); //gamma correction

            pixels[getIndex(x, y) + 0] = color[0] * 255;
            pixels[getIndex(x, y) + 1] = color[1] * 255;
            pixels[getIndex(x, y) + 2] = color[2] * 255;
        }
    }
    writeToPPM(pixels, "image.ppm");

    system("ppm_loader.exe image.ppm");
}
