#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "aabb.h"

using namespace std;

class BVH_Node: public Hitable
{
    Hitable *left;
    Hitable *right;
    AABB box;

    public:
        BVH_Node();
        BVH_Node(Hitable **list, int size, float time0, float time1);

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;
        virtual bool boundingBox(float time0, float time1, AABB &box) const;

        virtual ~BVH_Node();
};

bool boxXCompare(const Hitable *ah, const Hitable *bh);
bool boxYCompare(const Hitable *ah, const Hitable *bh);
bool boxZCompare(const Hitable *ah, const Hitable *bh);

#endif // BVH_NODE_H
