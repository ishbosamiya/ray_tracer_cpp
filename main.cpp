#include <iostream>
#include <cstdlib>
#include <fstream>

#include "vec3.h"
#include "ray.h"

using namespace std;

const float multiplier = 0.5;
const int width = 1280 * multiplier;
const int height = 720 * multiplier;

void writeToPPM(char *components, char *path);
Vec3 backgroundColor(Ray &ray);

int getIndex(int x, int y) {
    return (x + y * width) * 3;
}

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

Vec3 backgroundColor(Ray &ray) {
    Vec3 unit_direction = ray.directionVector().normalized();
    float t = 0.5 * (unit_direction.y() + 1.0);
    return Vec3(1.0, 1.0, 1.0)*(1.0 - t) + Vec3(0.5, 0.7, 1.0)*t;
}
