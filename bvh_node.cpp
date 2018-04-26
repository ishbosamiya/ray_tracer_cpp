#include "bvh_node.h"

extern float randomBetweenZeroOne();

BVH_Node::BVH_Node() {
    //ctor
}

BVH_Node::BVH_Node(Hitable **list, int size, float time0, float time1) {
    int axis = 3 * randomBetweenZeroOne();
    if(axis == 0) {
        sort(list, list + sizeof(list)/sizeof(*list), boxXCompare);
    }
    else if(axis == 1) {
        sort(list, list + sizeof(list)/sizeof(*list), boxYCompare);
    }
    else {
        sort(list, list + sizeof(list)/sizeof(*list), boxZCompare);
    }

    if(size == 1) {
        left = right = list[0];
    }
    else if(size == 2) {
        left = list[0];
        right = list[1];
    }
    else {
        left = new BVH_Node(list, size/2, time0, time1);
        right = new BVH_Node(list + size/2, size - size/2, time0, time1);
    }
    AABB box_left, box_right;
    if(!left->boundingBox(time0, time1, box_left) || !right->boundingBox(time0, time1, box_right)) {
        cerr << "No bounding box in BVH_Node constructor" << endl;
    }
    box = surroundingBox(box_left, box_right);
}


bool BVH_Node::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    if(box.hit(ray, t_min, t_max)) {
        Hit_Record left_record, right_record;
        bool hit_left = left->hit(ray, t_min, t_max, left_record);
        bool hit_right = right->hit(ray, t_min, t_max, right_record);
        if(hit_left && hit_right) {
            if(left_record.t < right_record.t) {
                record = left_record;
            }
            else {
                record = right_record;
            }
        }
        else if(hit_left) {
            record = left_record;
            return true;
        }
        else if(hit_right) {
            record = right_record;
            return true;
        }
        else {
            return false;
        }
        return true;
    }
    return false;
}

bool BVH_Node::boundingBox(float time0, float time1, AABB &box) const {
    box = this->box;
    return true;
}

BVH_Node::~BVH_Node() {
    //dtor
}

bool boxXCompare(const Hitable *ah, const Hitable *bh) {
    AABB box_left, box_right;
    if(!ah->boundingBox(0.0, 0.0, box_left) || !bh->boundingBox(0.0, 0.0, box_right)) {
        cerr << "No bounding box in BVH_Node constructor" << endl;
    }
    if(box_left.min().x() - box_right.min().x() < 0.0) {
        return false;
    }
    else {
        return true;
    }
}

bool boxYCompare(const Hitable *ah, const Hitable *bh) {
    AABB box_left, box_right;
    if(!ah->boundingBox(0.0, 0.0, box_left) || !bh->boundingBox(0.0, 0.0, box_right)) {
        cerr << "No bounding box in BVH_Node constructor" << endl;
    }
    if(box_left.min().y() - box_right.min().y() < 0.0) {
        return false;
    }
    else {
        return true;
    }
}

bool boxZCompare(const Hitable *ah, const Hitable *bh) {
    AABB box_left, box_right;
    if(!ah->boundingBox(0.0, 0.0, box_left) || !bh->boundingBox(0.0, 0.0, box_right)) {
        cerr << "No bounding box in BVH_Node constructor" << endl;
    }
    if(box_left.min().z() - box_right.min().z() < 0.0) {
        return false;
    }
    else {
        return true;
    }
}
