#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

class Hitable_List: public Hitable
{
    Hitable **list;
    int list_size;
    public:
        Hitable_List();
        Hitable_List(Hitable **list, int list_size);

        virtual bool hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const;
        virtual bool boundingBox(float time0, float time1, AABB &box) const;

        virtual ~Hitable_List();
};

#endif // HITABLE_LIST_H
