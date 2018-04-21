#include <iostream>
#include <cstdlib>
#include <fstream>

#include "vec3.h"

using namespace std;

const float multiplier = 0.5;
const int width = 1280 * multiplier;
const int height = 720 * multiplier;

void writeToPPM(char *components, char *path);

int getIndex(int x, int y) {
    return (x + y * width) * 3;
}

int main() {
    char *pixels = new char[width * height * 3];
    for(int y = height - 1; y >= 0; y--) {
        for(int x = 0; x < width; x++) {
            float r = (float)x / (float)width;
            float g = (float)(y) / (float)height;
            float b = 0.2;

            pixels[getIndex(x, y) + 0] = r * 255;
            pixels[getIndex(x, y) + 1] = g * 255;
            pixels[getIndex(x, y) + 2] = b * 255;
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
