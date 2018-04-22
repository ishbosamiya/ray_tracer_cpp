#include <iostream>
#include <cstdlib>
#include <fstream>

#include "functions.h"
#include "sphere.h"
#include "hitable.h"
#include "hitable_list.h"
#include "camera.h"

using namespace std;

//const float multiplier = 0.5;
//const int width = 1280 * multiplier;
//const int height = 720 * multiplier;

const float multiplier = 0.5;
const int width = 1280 * multiplier;
const int height = 720 * multiplier;
const int no_of_samples = 5;


int main() {
    srand(time(0));

    char *pixels = new char[width * height * 3];

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new Sphere(Vec3(0.0, -100.5, -1.0), 100);
    Hitable *world = new Hitable_List(list, 2);

    Camera camera;

    for(int y = height - 1; y >= 0; y--) {
        for(int x = 0; x < width; x++) {
            Vec3 color(0.0, 0.0, 0.0);
            for(int s = 0; s < no_of_samples; s++) {
                float u = ((float)x + randomBetweenZeroOne())/ (float)width;
                float v = ((float)y + randomBetweenZeroOne())/ (float)height;

                Ray ray = camera.getRay(u, v);

                Vec3 p = ray.pointAtParameter(2.0);

                color += backgroundColor(ray, world);
            }

            color /= (float)no_of_samples;

            pixels[getIndex(x, y) + 0] = color[0] * 255;
            pixels[getIndex(x, y) + 1] = color[1] * 255;
            pixels[getIndex(x, y) + 2] = color[2] * 255;
        }
    }
    cout << "Ray Tracing Is Done" << endl;
    writeToPPM(pixels, "image.ppm");

    system("ppm_loader.exe image.ppm");
}
