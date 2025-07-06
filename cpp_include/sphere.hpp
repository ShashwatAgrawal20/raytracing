#pragma once
#include "hitable.hpp"

class sphere : public hitable {
   public:
    vec3 center;
    double radius;
    sphere(vec3 cen, double r) : center(cen), radius(r) {}

    bool hit(const Ray& r, double t_min, double t_max,
             hit_record& rec) const override {
        vec3 oc = r.origin - center;
        double a = dot(r.direction, r.direction);
        double b = dot(oc, r.direction);
        double c = dot(oc, oc) - radius * radius;
        double disc = b * b - a * c;
        if (disc > 0) {
            double temp = (-b - sqrt(b * b - a * c)) / a;
            if (temp < t_max && temp > t_min) {
                rec.t = temp;
                rec.p = r.point_at_param(rec.t);
                rec.normal = (rec.p - center) / radius;
                return true;
            }
            temp = (-b + sqrt(b * b - a * c)) / a;
            if (temp < t_max && temp > t_min) {
                rec.t = temp;
                rec.p = r.point_at_param(rec.t);
                rec.normal = (rec.p - center) / radius;
                return true;
            }
        }
        return false;
    }
};
