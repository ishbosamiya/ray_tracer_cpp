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
#include "bvh_node.h"

using namespace std;

float multiplier = 1.0;
int width = 1280 * multiplier;
int height = 720 * multiplier;
int no_of_samples = 1;
int total_samples = no_of_samples * width * height;

void getSettings() {
    ifstream fin;
    fin.open("settings.txt");
    if(!fin.is_open()) {
        cout << "Setting file not found, creating new one" << endl;
        cout << "Order: multiplier, width, height, no of samples" << endl;
        ofstream fout;
        fout.open("settings.txt");
        fout << multiplier << endl;
        fout << width << endl;
        fout << height << endl;
        fout << no_of_samples << endl;
        fout.close();
        return;
    }
    fin >> multiplier >> width >> height >> no_of_samples;
    width *= multiplier;
    height *= multiplier;
    cout << "***Settings***" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Number of samples: " << no_of_samples << endl;
}

int main() {
    getSettings();
    total_samples = no_of_samples * width * height;

    srand(time(0));

    char *pixels = new char[width * height * 3];

    int list_size;
    Hitable **list = randomScene(list_size);
    BVH_Node *world = new BVH_Node(list, list_size, 0.0, 0.0);

    //Camera Properties
    Vec3 look_from(9.5, 2.0, 3.5);
    Vec3 look_at(0.0, 0.7, -1.0);
    float aperture = 30.0;
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
