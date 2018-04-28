#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

extern float multiplier;
extern int width;
extern int height;
extern int no_of_samples;
extern int total_samples;

int getIndex(int x, int y);
void writeToPPM(char *components, char *path);
Vec3 backgroundColor(Ray &ray, Hitable *world, int depth);
float randomBetweenZeroOne();
Vec3 randomInUnitSphere();
Vec3 randomInUnitDisk();
void percentageCompleted();
Hitable **randomScene(int &size);
int getMilliCount();
void printTime(long long int time);

Hitable **setupGridOfSpheres(Vec3 &look_from, Vec3 &look_at, float &aperture, float &fov, int grid_size, int &list_size);

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

Vec3 backgroundColor(Ray &ray, Hitable *world, int depth) {
    Hit_Record record;
    if(world->hit(ray, 0.001, 10000.0, record)) {
        Ray scattered;
        Vec3 attenuation;
        if(depth < 50 && record.material_pointer->scatter(ray, record, attenuation, scattered)) {
            return attenuation*backgroundColor(scattered, world, depth+1);
        }
        else {
            return Vec3(0.0, 0.0, 0.0);
        }
    }
    else {
        Vec3 unit_direction = ray.directionVector().normalized();
        float t = (unit_direction.y() + 1.0)*0.5;
        return Vec3(1.0, 1.0, 1.0)*(1.0 - t) + Vec3(0.5, 0.7, 1.0)*t;
    }
}

float randomBetweenZeroOne() {
    return ((double)rand()/RAND_MAX);
}

Vec3 randomInUnitSphere() {
    Vec3 p;

    do {
        p = Vec3(randomBetweenZeroOne(), randomBetweenZeroOne(), randomBetweenZeroOne())*2.0 - Vec3(1.0, 1.0, 1.0);
    } while(p.squaredLength() >= 1.0);

    return p;
}

Vec3 randomInUnitDisk() {
    Vec3 p;
    do {
        p = (Vec3(randomBetweenZeroOne(), randomBetweenZeroOne(), 0.0)*2.0) - Vec3(1.0, 1.0, 0.0);
    } while(p.dot(p) >= 1.0);
    return p;
}

void percentageCompleted() {
    static int inital_time = getMilliCount();
    static float one_over_total_samples = 1.0/total_samples;
    static float previous_percentage = 0;
    static int current_count = 1;
    float current_percentage = current_count * one_over_total_samples * 100;
    if((int)(current_percentage*100.0) > (int)(previous_percentage*100.0)) {
        previous_percentage = current_percentage;
        int temp = current_percentage * 100;
        cout << "\rRay Tracing Progress: " << temp/100.0 << "%";
        long long int time_elapsed = getMilliCount() - inital_time;
        long long int time_left = (time_elapsed * total_samples / current_count) - (time_elapsed);
        cout << " Time Left: "; printTime(time_left/1000);
        cout << " Time Elapsed: "; printTime(time_elapsed/1000);
        cout << "                 ";
    }
    if(current_count >= total_samples) {
        system("cls");
        cout << "Ray Tracing Done!!! " << "Took "; printTime((getMilliCount() - inital_time)/1000);
        cout << "                                   " << endl;
    }

    current_count++;
}

Hitable **randomScene(int &size) {
    Hitable **list;
    size = 500;
    list = new Hitable*[size+1];
    list[0] = new Sphere(Vec3(0.0, -1000.0, 0), 1000.0, new Lambertian(new Checker_Texture( new Constant_Texture(Vec3(0.2, 0.5, 0.1)),
                                                                                           new Constant_Texture(Vec3(0.9, 0.9, 0.9)))));
    int i = 1;
    for(int a = -11; a < 11; a++) {
        for(int b = -11; b < 11; b++) {
            float choose_mat = randomBetweenZeroOne();
            Vec3 center(a+0.9*randomBetweenZeroOne(), 0.2, b+0.9*randomBetweenZeroOne());
            if((center - Vec3(4.0, 0.2, 0.0)).length() > 0.9) {
                if(choose_mat < 0.7) {
                    list[i++] = new Sphere(center, 0.2, new Lambertian(new Constant_Texture(Vec3(randomBetweenZeroOne()*randomBetweenZeroOne(),
                                                                            randomBetweenZeroOne()*randomBetweenZeroOne(),
                                                                            randomBetweenZeroOne()*randomBetweenZeroOne()))));
                }
                else if(choose_mat < 0.9) {
                    list[i++] = new Sphere(center, 0.2, new Metal(Vec3(randomBetweenZeroOne()*randomBetweenZeroOne(),
                                                                            randomBetweenZeroOne()*randomBetweenZeroOne(),
                                                                            randomBetweenZeroOne()*randomBetweenZeroOne()),
                                                                  0.2*randomBetweenZeroOne()));
                }
                else {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5, 0.003*randomBetweenZeroOne()));
                }
            }
        }
    }
    list[i++] = new Sphere(Vec3(0.0, 1.0, 0.0), 1.0, new Dielectric(1.5, 0.003));
    list[i++] = new Sphere(Vec3(-4.0, 1.0, 0.0), 1.0, new Lambertian(new Constant_Texture(Vec3(0.32, 0.95, 0.82))));
    list[i++] = new Sphere(Vec3(4.0, 1.0, 0.0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.04));

    size = i;
    return list;
}

int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

void printTime(long long int time) {
    if(time < 60) {
        cout << time << "s";
    }
    else if(time < 3600) {
        cout << time/60 << "min " << time%60 << "s";
    }
    else if(time < 86400) {
        cout << time/3600 << "hrs " << (time%3600)/60 << "min " << time%60 << "s";
    }
    else {
        cout << time/86400 << "days " << (time%86400)/3600 << "hrs " << (time%3600)/60 << "min " << time%60 << "s";
    }
}

Hitable **setupGridOfSpheres(Vec3 &look_from, Vec3 &look_at, float &aperture, float &fov, int grid_size, int &list_size) {
    int no_of_mats = 5;
    Material **mats;
    mats = new Material*[no_of_mats];
    mats[0] = new Lambertian( new Constant_Texture(Vec3(0.2, 0.6, 0.6)));
    mats[1] = new Metal(Vec3(0.8, 0.8, 0.8), 0.05);
    mats[2] = new Dielectric(1.5, 0.01);
    mats[3] = new Lambertian( new Checker_Texture(new Constant_Texture(Vec3(0.9, 0.9, 0.9)),
                                                  new Constant_Texture(Vec3(0.2, 0.3, 0.1)), 20));
    mats[4] = new Lambertian( new Fresnel_Texture(1.5));

    float root_2 = sqrt(2.0);
    list_size = grid_size * grid_size;
    Hitable **list = new Hitable*[list_size];
    float radius = 1.0;
    Vec3 lower_left;
    if(grid_size % 2 == 0) {
        lower_left = Vec3( -root_2 * grid_size * radius * 0.5, -root_2 * grid_size * radius * 0.5, -1.0);
    }
    else {
        lower_left = Vec3(-1.0*radius*(grid_size - 1.0), -1.0*radius*(grid_size - 1.0), -1.0);
    }
    for(int x = 0; x < grid_size; x++) {
        for(int y = 0; y < grid_size; y++) {
            list[x + y * grid_size] = new Sphere(lower_left + Vec3((float)x*2.0*radius, (float)y*2.0*radius, 0.0), radius, mats[(int)(randomBetweenZeroOne()*no_of_mats) % no_of_mats]);
        }
    }

    //Camera Properties
    look_from = Vec3(0.0, 0.0, grid_size * 2.0 * radius);
    look_at = Vec3(0.0, 0.0, -1.0);
    aperture = 0.0; //this setting is the opposite to a real camera, larger value causes more depth of field
    fov = 60.0;

    return list;
}

#endif // FUNCTIONS_H
