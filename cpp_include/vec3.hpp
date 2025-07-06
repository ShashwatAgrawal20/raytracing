#pragma once

#include <cmath>

class vec3 {
   public:
    double x;
    double y;
    double z;

    vec3() {}
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
    vec3 operator/(const double& other) const {
        return vec3(x / other, y / other, z / other);
    }
};

inline double dot(const vec3& v1, const vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
