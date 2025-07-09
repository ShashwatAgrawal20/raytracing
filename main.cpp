#include <iostream>
#include <memory>

#include "cpp_include/camera.hpp"
#include "cpp_include/hitable.hpp"
#include "cpp_include/hitable_list.hpp"
#include "cpp_include/ray.hpp"
#include "cpp_include/sphere.hpp"
#include "cpp_include/vec3.hpp"

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = (vec3(drand48(), drand48(), drand48()) * 2.0) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

vec3 color(const Ray& r, hitable* world) {
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return color(Ray(rec.p, target - rec.p), world) * 0.5;
    }
    vec3 unit_vector = r.direction.unit_vector();
    float t = 0.5 * (unit_vector.y + 1.0);
    return vec3((vec3(1.0, 1.0, 1.0) * (1.0 - t)) + (vec3(0.5, 0.7, 1.0) * t));
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255" << std::endl;

    std::unique_ptr<hitable> list[2];
    list[0] = std::make_unique<sphere>(vec3(0, 0, -1), 0.5);
    list[1] = std::make_unique<sphere>(vec3(0, -100.5, -1), 100);

    hitable* raw_list[2] = {list[0].get(), list[1].get()};

    auto world = std::make_unique<hitable_list>(raw_list, 2);
    camera cam;

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; ++s) {
                double u = static_cast<double>(i + drand48()) / nx;
                double v = static_cast<double>(j + drand48()) / ny;
                Ray r = cam.get_ray(u, v);
                // vec3 p = r.point_at_param(2.0);
                col += color(r, world.get());
            }

            col /= double(ns);

            int ir = (255.99 * col.x);
            int ig = (255.99 * col.y);
            int ib = (255.99 * col.z);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    return 0;
}
