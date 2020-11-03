#include "../include/Plane.h"

// constructor
Plane::Plane(Vector3 position, Vector3 normal): Object(position), normal(normal) {}

RayHit* Plane::intersectsWith(const Ray& ray) const{
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    Plane plane = (*this);
    float denom = ray.direction.dot(plane.normal);
    if(denom > 1e-6) {
        float t = (plane.position - ray.origin).dot(plane.normal) / denom;
        Vector3 hitNormal = ray.direction.dot(plane.normal) > 0 ? normal : normal * -1;
        RayHit* hit = new RayHit(ray.origin + ray.direction * t, hitNormal, t);
        return hit;
    }
    return nullptr;
}
