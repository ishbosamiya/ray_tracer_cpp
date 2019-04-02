#include "box.h"

Box::Box(Vec3 pmin, Vec3 pmax, Material *material) {
    this->pmin = pmin;
    this->pmax = pmax;

    Hitable **list = new Hitable*[6];
    list[0] = new XY_Rect(pmin.x(), pmax.x(), pmin.y(), pmax.y(), pmax.z(), material);
    list[1] = new Flip_Normals(new XY_Rect(pmin.x(), pmax.x(), pmin.y(), pmax.y(), pmin.z(), material));
    list[2] = new XZ_Rect(pmin.x(), pmax.x(), pmin.z(), pmax.z(), pmax.y(), material);
    list[3] = new Flip_Normals(new XZ_Rect(pmin.x(), pmax.x(), pmin.z(), pmax.z(), pmin.y(), material));
    list[4] = new YZ_Rect(pmin.y(), pmax.y(), pmin.z(), pmax.z(), pmax.x(), material);
    list[5] = new Flip_Normals(new YZ_Rect(pmin.y(), pmax.y(), pmin.z(), pmax.z(), pmin.x(), material));
    list_ptr = new BVH_Node(list, 6, 0.0, 0.0);
}

bool Box::hit(Ray &ray, float t_min, float t_max, Hit_Record &record) const {
    return list_ptr->hit(ray, t_min, t_max, record);
}

bool Box::boundingBox(float time0, float time1, AABB &box) const {
    box = AABB(pmin, pmax);
    return true;
}
