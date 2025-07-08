#pragma once

#include "ray.hpp"
#include "vec3.hpp"

class camera {
   public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    camera()
        : origin(0.0, 0.0, 0.0),
          lower_left_corner(-2.0, -1.0, -1.0),
          horizontal(4.0, 0.0, 0.0),
          vertical(0.0, 2.0, 0.0) {}

    Ray get_ray(double u, double v) {
        return Ray(origin, lower_left_corner + (horizontal * u) +
                               (vertical * v) - origin);
    }
};
