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
#include "texture.h"
#include "rectangles.h"
#include "test_scenes.h"

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
    Vec3 *pixels_temp = new Vec3[width * height];

    //Camera Properties
    Vec3 look_from(278.0, 278.0, -800.0);
    Vec3 look_at(278.0, 278.0, 0.0);
    float distance_to_focus = 10.0;
    float aperture = 0.0; //this setting is the opposite to a real camera, larger value causes more depth of field
    float fov = 40.0;

    BVH_Node *world = cornellBoxSmoke();

    Camera camera(look_from, look_at, Vec3(0.0, 1.0, 0.0), fov, (float)width/(float)height, aperture, distance_to_focus);

    for(int s = 0; s < no_of_samples; s++) {
        for(int y = height - 1; y >= 0; y--) {
            for(int x = 0; x < width; x++) {
                Vec3 color(0, 0, 0);
                color = pixels_temp[x + y * width];

                float u = ((float)x + randomBetweenZeroOne())/ (float)width;
                float v = ((float)y + randomBetweenZeroOne())/ (float)height;

                Ray ray = camera.getRay(u, v);

                Vec3 p = ray.pointAtParameter(2.0);

                color += backgroundColor(ray, world, 0);

                percentageCompleted(); //gives report of how much of the ray tracing is done

                Vec3 temp_color = color/(float)(s+1.0);

                temp_color = Vec3(sqrt(temp_color[0]), sqrt(temp_color[1]), sqrt(temp_color[2])); //gamma correction

                pixels_temp[x + y * width] = color;
                pixels[getIndex(x, y) + 0] = max(min(temp_color[0] * 255, 255.0f), 0.0f);
                pixels[getIndex(x, y) + 1] = max(min(temp_color[1] * 255, 255.0f), 0.0f);
                pixels[getIndex(x, y) + 2] = max(min(temp_color[2] * 255, 255.0f), 0.0f);
            }
        }
        if((s + 1) % 4 == 0) {
            writeToPPM(pixels, "image.ppm", s + 1);
        }
        if(s == 0) {
            writeToPPM(pixels, "image.ppm", s + 1);
            system("start ppm_loader.exe image.ppm");
        }
        else if(s == no_of_samples - 1) {
            system("Taskkill /IM ppm_loader.exe");
        }
//        else {
//            system("Taskkill /IM ppm_loader.exe");
//            system("start ppm_loader.exe image.ppm");
//        }
    }

    writeToPPM(pixels, "image.ppm", no_of_samples);

    system("ppm_loader.exe image.ppm");
}
