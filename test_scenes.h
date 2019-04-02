#ifndef TEST_SCENES_H
#define TEST_SCENES_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "texture.h"
#include "rectangles.h"
#include "sphere.h"
#include "bvh_node.h"
#include "box.h"
#include "constant_medium.h"

BVH_Node *simpleLight() {
    Texture *perlin_texture = new Noise_Texture(4);
    Hitable **list = new Hitable*[4];
    list[0] = new Sphere(Vec3(0.0, -1000.0, 0.0), 1000.0, new Lambertian(perlin_texture));
    list[1] = new Sphere(Vec3(0.0, 2.0, 0.0), 2.0, new Lambertian(perlin_texture));
    list[2] = new Sphere(Vec3(0.0, 7.0, 0.0), 2.0, new Diffuse_Light(new Constant_Texture(Vec3(0.0, 0.0, 0.0))));
    list[3] = new XY_Rect(3.0, 5.0, 1.0, 3.0, -2.0, new Diffuse_Light(new Constant_Texture(Vec3(4.0, 4.0, 4.0))));
    return new BVH_Node(list, 4, 0.0, 0.0);
}

BVH_Node *cornellBox() {
    Hitable **list = new Hitable*[8];
    int i = 0;
    Material *red = new Lambertian(new Constant_Texture(Vec3(0.65, 0.05, 0.05)));
    Material *white = new Lambertian(new Constant_Texture(Vec3(0.73, 0.73, 0.73)));
    Material *green = new Lambertian(new Constant_Texture(Vec3(0.12, 0.45, 0.15)));
    Material *light = new Diffuse_Light(new Constant_Texture(Vec3(15, 15, 15)));

    list[i++] = new Flip_Normals(new YZ_Rect(0.0, 555.0, 0.0, 555.0, 555.0, green));
    list[i++] = new YZ_Rect(0.0, 555.0, 0.0, 555.0, 0, red);
    list[i++] = new XZ_Rect(213.0, 343.0, 227.0, 332.0, 554.0, light);
    list[i++] = new Flip_Normals(new XZ_Rect(0.0, 555.0, 0.0, 555.0, 555.0, white));
    list[i++] = new XZ_Rect(0.0, 555.0, 0.0, 555.0, 0.0, white);
    list[i++] = new Flip_Normals(new XY_Rect(0.0, 555.0, 0.0, 555.0, 555.0, white));

    list[i++] = new Translate( new Rotate_Y( new Box(Vec3(0.0, 0.0, 0.0), Vec3(165.0, 165.0, 165.0), white)
                                            , -18)
                              , Vec3(130.0, 0.0, 65.0));
    list[i++] = new Translate( new Rotate_Y( new Box(Vec3(0.0, 0.0, 0.0), Vec3(165.0, 330.0, 165.0), white)
                                            , 15)
                              , Vec3(265.0, 0.0, 295.0));

    return new BVH_Node(list, 8, 0.0, 0.0);
}

BVH_Node *cornellBoxSmoke() {
    Hitable **list = new Hitable*[8];
    int i = 0;
    Material *red = new Lambertian(new Constant_Texture(Vec3(0.65, 0.05, 0.05)));
    Material *white = new Lambertian(new Constant_Texture(Vec3(0.73, 0.73, 0.73)));
    Material *green = new Lambertian(new Constant_Texture(Vec3(0.12, 0.45, 0.15)));
    Material *light = new Diffuse_Light(new Constant_Texture(Vec3(7, 7, 7)));

    list[i++] = new Flip_Normals(new YZ_Rect(0.0, 555.0, 0.0, 555.0, 555.0, green));
    list[i++] = new YZ_Rect(0.0, 555.0, 0.0, 555.0, 0, red);
    list[i++] = new XZ_Rect(113.0, 443.0, 127.0, 432.0, 554.0, light);
    list[i++] = new Flip_Normals(new XZ_Rect(0.0, 555.0, 0.0, 555.0, 555.0, white));
    list[i++] = new XZ_Rect(0.0, 555.0, 0.0, 555.0, 0.0, white);
    list[i++] = new Flip_Normals(new XY_Rect(0.0, 555.0, 0.0, 555.0, 555.0, white));

    Hitable *b1 = new Translate( new Rotate_Y( new Box(Vec3(0.0, 0.0, 0.0), Vec3(165.0, 165.0, 165.0), white)
                                            , -18)
                              , Vec3(130.0, 0.0, 65.0));
    Hitable *b2 = new Translate( new Rotate_Y( new Box(Vec3(0.0, 0.0, 0.0), Vec3(165.0, 330.0, 165.0), white)
                                            , 15)
                              , Vec3(265.0, 0.0, 295.0));
    list[i++] = new Constant_Medium(b1, 0.01, new Constant_Texture(Vec3(1.0, 1.0, 1.0)));
    list[i++] = new Constant_Medium(b2, 0.01, new Constant_Texture(Vec3(0.0, 0.0, 0.0)));

    return new BVH_Node(list, 8, 0.0, 0.0);
}

#endif // TEST_SCENES_H
