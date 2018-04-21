#include <iostream>
#include <cstdlib>
#include <fstream>

#include "functions.h"

using namespace std;

const float multiplier = 0.5;
const int width = 1280 * multiplier;
const int height = 720 * multiplier;

int main() {
    char *pixels = new char[width * height * 3];

    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    for(int y = height - 1; y >= 0; y--) {
        for(int x = 0; x < width; x++) {
            float u = (float)x / (float)width;
            float v = (float)y / (float)height;

            Ray ray(origin, lower_left_corner + horizontal*u + vertical*v);

            Vec3 color = backgroundColor(ray);

            pixels[getIndex(x, y) + 0] = color[0] * 255;
            pixels[getIndex(x, y) + 1] = color[1] * 255;
            pixels[getIndex(x, y) + 2] = color[2] * 255;
        }
    }
    writeToPPM(pixels, "image.ppm");

    system("ppm_loader.exe image.ppm");
}
