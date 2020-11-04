#include "../include/Plane.h"

// constructor
Plane::Plane(const Vector3& position, Vector3 normal): Shape(position), normal(normal) {}
//destructor
Plane::~Plane(){}

bool Plane::intersectsWith(const Ray& ray, RayHit& hit) const{
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    Plane plane = (*this);
    float denom = ray.direction.dot(plane.normal);
    if(denom > 1e-6) {
        float t = (plane.position - ray.origin).dot(plane.normal) / denom;
        Vector3 hitNormal = ray.direction.dot(plane.normal) > 0 ? normal : normal * -1;
        Vector3 hitPoint = ray.origin + ray.direction * t;

        hit.point = hitPoint;
        hit.normal = hitNormal;
        hit.distance = t;
        return true;
    }
    return false;
}
