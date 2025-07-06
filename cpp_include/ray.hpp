#pragma once
#include "vec3.hpp"

struct Ray {
    vec3 origin;
    vec3 direction;
    vec3 point_at_param(double t) const { return origin + (direction * t); }
};

inline double hit_sphere(const vec3& center, double radius, const Ray& r) {
    vec3 oc = r.origin - center;
    double a = dot(r.direction, r.direction);
    double b = 2.0 * dot(oc, r.direction);
    double c = dot(oc, oc) - radius * radius;
    double disc = b * b - 4 * a * c;
    if (disc < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(disc)) / (2.0 * a);
    }
}
