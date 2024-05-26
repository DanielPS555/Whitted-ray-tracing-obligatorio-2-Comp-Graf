#include <iostream>
#include <cmath>
#include <FreeImage.h>

// Define a simple structure for a 3D vector
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

// Ray structure
struct Ray {
    Vec3 origin, direction;
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction.normalize()) {}
};

// Sphere structure
struct Sphere {
    Vec3 center;
    float radius;
    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}
    bool intersect(const Ray& ray, float& t) const {
        Vec3 oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return false;
        t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        return true;
    }
};

// Trace function
Vec3 trace(const Ray& ray, const Sphere& sphere) {
    float t;
    if (sphere.intersect(ray, t)) {
        Vec3 hitPoint = ray.origin + ray.direction * t;
        Vec3 normal = (hitPoint - sphere.center).normalize();
        return Vec3(1, 0, 0) * std::max(0.0f, normal.dot(Vec3(0, 0, -1)));  // Simple diffuse shading
    }
    return Vec3(0.5, 0.7, 1.0);  // Background color
}

void dibujar(int width, int height, FIBITMAP* bitmap) {
    Vec3 camera(0, 0, 0);
    Vec3 sphereCenter(0, 0, -5);
    float sphereRadius = 1;
    Sphere sphere(sphereCenter, sphereRadius);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float u = (x + 0.5f) / width;
            float v = (y + 0.5f) / height;
            Vec3 rayDirection(u * 2 - 1, v * 2 - 1, -1);  // Simple orthographic projection
            Ray ray(camera, rayDirection);
            Vec3 color = trace(ray, sphere);
            RGBQUAD rgbColor;
            rgbColor.rgbRed = (BYTE)(color.x * 255);
            rgbColor.rgbGreen = (BYTE)(color.y * 255);
            rgbColor.rgbBlue = (BYTE)(color.z * 255);
            FreeImage_SetPixelColor(bitmap, x, height - y - 1, &rgbColor);  // FreeImage uses bottom-left origin
        }
    }
}
