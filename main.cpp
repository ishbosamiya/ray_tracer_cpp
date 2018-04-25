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


int main() {
    const float multiplier = 1.0;
    const int width = 1280 * multiplier;
    const int height = 720 * multiplier;
    const int no_of_samples = 100;
    const int total_samples = no_of_samples * width * height;

    srand(time(0));

    char *pixels = new char[width * height * 3];

    Hitable *world = randomScene();

    //Camera Properties
//    Vec3 look_from(-0.45, 0.5, 0.066);
//    Vec3 look_at(0.0, 0.0, -1.0);
//    float aperture = 0.35;
//    float fov = 70;
//    Vec3 look_from(11.0, 3.5, 7.0);
//    Vec3 look_at(0.0, 0.0, -1.0);
//    float aperture = 3.0;
//    float fov = 30.0;
    Vec3 look_from(9.5, 2.0, 3.5);
    Vec3 look_at(0.0, 0.7, -1.0);
    float aperture = 0.1;
    float fov = 30.0;
    Camera camera(look_from, look_at, Vec3(0.0, 1.0, 0.0), fov, (float)width/(float)height, aperture, (look_from - look_at).length());

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
