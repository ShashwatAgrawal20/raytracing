#pragma once

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
   public:
    virtual bool hit(const Ray& r, double t_min, double t_max,
                     hit_record& rec) const = 0;

    virtual ~hitable() = default;
};
