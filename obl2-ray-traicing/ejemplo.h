#ifndef EJEMPLO_H
#define EJEMPLO_H

#include <FreeImage.h>
#include <stdio.h>
#include <iostream>

struct Vec3 {
    float x, y, z;
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
    Vec3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / length, y / length, z / length);
    }
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
};


struct Ray {
    Vec3 origin, direction;
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction.normalize()) {}
};


struct Sphere {
    Vec3 center;
    float radius;
    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}
    bool intersect(const Ray& ray, float& t) const;
};


Vec3 trace(const Ray& ray, const Sphere& sphere);


void dibujar(int width, int height, FIBITMAP* bitmap);

#endif // EJEMPLO_H