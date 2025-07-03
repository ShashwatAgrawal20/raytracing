#include <cmath>
#include <iostream>

class vec3;
struct Ray;
double dot(const vec3& v1, const vec3& v2);
bool hit_sphere(const vec3& center, double radius, const Ray& r);

class vec3 {
   public:
    double x;
    double y;
    double z;

    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    double length() const { return std::sqrt(x * x + y * y + z * z); }

    vec3 unit_vector() const {
        double len = length();
        return vec3(x / len, y / len, z / len);
    }

    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }
    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    vec3 operator*(const double& other) const {
        return vec3(x * other, y * other, z * other);
    }
};

struct Ray {
    vec3 origin;
    vec3 direction;
    vec3 color(bool want_sphere = false) const {
        if (want_sphere && hit_sphere(vec3(0, 0, -1), 0.5, *this))
            return vec3(1, 0, 0);
        vec3 unit_vector = direction.unit_vector();
        float t = 0.5 * (unit_vector.y + 1.0);
        return vec3((vec3(1.0, 1.0, 1.0) * (1.0 - t)) +
                    (vec3(0.5, 0.7, 1.0) * t));
    }
};

double dot(const vec3& v1, const vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

bool hit_sphere(const vec3& center, double radius, const Ray& r) {
    vec3 oc = r.origin - center;
    double a = dot(r.direction, r.direction);
    double b = 2.0 * dot(oc, r.direction);
    double c = dot(oc, oc) - radius * radius;
    double disc = b * b - 4 * a * c;
    return (disc > 0);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255" << std::endl;

    vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);
    vec3 horizontal = vec3(4.0, 0.0, 0.0);
    vec3 vertical = vec3(0.0, 2.0, 0.0);
    vec3 origin = vec3(0.0, 0.0, 0.0);

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            double u = static_cast<double>(i) / nx;
            double v = static_cast<double>(j) / ny;

            Ray ray = {.origin = origin,
                       .direction = lower_left_corner + (horizontal * u) +
                                    (vertical * v)};
            vec3 col = ray.color(true);

            int ir = (255.99 * col.x);
            int ig = (255.99 * col.y);
            int ib = (255.99 * col.z);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    return 0;
}
