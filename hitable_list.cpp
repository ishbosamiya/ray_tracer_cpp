#include "hitable_list.h"

Hitable_List::Hitable_List() {
    list = nullptr;
    list_size = 0;
}

Hitable_List::Hitable_List(Hitable **list, int list_size) {
    this->list = list;
    this->list_size = list_size;
}

bool Hitable_List::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    Hit_Record temp_record;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(int i = 0; i < list_size; i++) {
        if(list[i]->hit(ray, t_min, closest_so_far, temp_record)) {
            hit_anything = true;
            closest_so_far = temp_record.t;
            record = temp_record;
        }
    }
    return hit_anything;
}

Hitable_List::~Hitable_List()
{
    //dtor
}
