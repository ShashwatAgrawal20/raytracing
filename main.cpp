#include <iostream>
#include <memory>

#include "cpp_include/hitable.hpp"
#include "cpp_include/hitable_list.hpp"
#include "cpp_include/ray.hpp"
#include "cpp_include/sphere.hpp"
#include "cpp_include/vec3.hpp"

vec3 color(const Ray& r, hitable* world) {
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return (vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1) *
                0.5);
    }
    vec3 unit_vector = r.direction.unit_vector();
    float t = 0.5 * (unit_vector.y + 1.0);
    return vec3((vec3(1.0, 1.0, 1.0) * (1.0 - t)) + (vec3(0.5, 0.7, 1.0) * t));
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255" << std::endl;

    vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);
    vec3 horizontal = vec3(4.0, 0.0, 0.0);
    vec3 vertical = vec3(0.0, 2.0, 0.0);
    vec3 origin = vec3(0.0, 0.0, 0.0);

    std::unique_ptr<hitable> list[2];
    list[0] = std::make_unique<sphere>(vec3(0, 0, -1), 0.5);
    list[1] = std::make_unique<sphere>(vec3(0, -100.5, -1), 100);

    hitable* raw_list[2] = {list[0].get(), list[1].get()};

    auto world = std::make_unique<hitable_list>(raw_list, 2);

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            double u = static_cast<double>(i) / nx;
            double v = static_cast<double>(j) / ny;

            Ray ray = {.origin = origin,
                       .direction = lower_left_corner + (horizontal * u) +
                                    (vertical * v)};

            // vec3 p = ray.point_at_param(2.0);
            vec3 col = color(ray, world.get());

            int ir = (255.99 * col.x);
            int ig = (255.99 * col.y);
            int ib = (255.99 * col.z);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    return 0;
}
