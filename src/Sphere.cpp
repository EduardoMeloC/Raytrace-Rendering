#include "../include/Sphere.h"

// constructor
Sphere::Sphere(Vector3 position, float radius): Shape(position), radius(radius), radius2(radius*radius){}

RayHit* Sphere::intersectsWith(const Ray& ray) const{
    // We'll use the geometric approach
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    Sphere sphere = (*this);

    Vector3 L = sphere.position - ray.origin;
    float tca = L.dot(ray.direction);
    if(tca < 0) return nullptr;
    float d2 = L.dot(L) - tca * tca;
    if(d2 > sphere.radius2) return nullptr;
    float thc = sqrt(sphere.radius2 - d2);

    float t0 = tca - thc;
    float t1 = tca + thc;
    if (t0 > t1) std::swap(t0, t1);
    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return nullptr;
    }

    float distance = t0;
    Vector3 point = ray.origin + ray.direction * distance;
    Vector3 normal = (point - sphere.position).normalized();

    RayHit* hit = new RayHit(point, normal, distance);
    return hit;
}
