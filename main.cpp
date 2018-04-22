#include <iostream>
#include <cstdlib>
#include <fstream>

#include "functions.h"
#include "sphere.h"
#include "hitable.h"
#include "hitable_list.h"

using namespace std;

//const float multiplier = 0.5;
//const int width = 1280 * multiplier;
//const int height = 720 * multiplier;

const float multiplier = 4;
const int width = 200 * multiplier;
const int height = 100 * multiplier;


int main() {
    char *pixels = new char[width * height * 3];

    Vec3 lower_left_corner(-2, -1, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new Sphere(Vec3(0.0, -100.5, -1.0), 100);
    Hitable *world = new Hitable_List(list, 2);

    for(int y = height - 1; y >= 0; y--) {
        for(int x = 0; x < width; x++) {
            float u = (float)x / (float)width;
            float v = (float)y / (float)height;

            Ray ray(origin, lower_left_corner + horizontal*u + vertical*v);

            Vec3 p = ray.pointAtParameter(2.0);
            Vec3 color = backgroundColor(ray, world);

            pixels[getIndex(x, y) + 0] = color[0] * 255;
            pixels[getIndex(x, y) + 1] = color[1] * 255;
            pixels[getIndex(x, y) + 2] = color[2] * 255;
        }
    }
    writeToPPM(pixels, "image.ppm");

    system("ppm_loader.exe image.ppm");
}
