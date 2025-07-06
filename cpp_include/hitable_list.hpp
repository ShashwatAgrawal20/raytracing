#pragma once

#include "hitable.hpp"

class hitable_list : public hitable {
   public:
    hitable** list;
    int list_size;
    hitable_list() {}
    hitable_list(hitable** l, int n) : list(l), list_size(n) {}
    bool hit(const Ray& r, double t_min, double t_max,
             hit_record& rec) const override {
        hit_record hit_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;
        for (int i = 0; i < list_size; ++i) {
            if (list[i]->hit(r, t_min, closest_so_far, hit_rec)) {
                hit_anything = true;
                closest_so_far = hit_rec.t;
                rec = hit_rec;
            }
        }
        return hit_anything;
    }
};
