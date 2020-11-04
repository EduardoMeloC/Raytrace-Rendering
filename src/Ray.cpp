#include "../include/Ray.h"

// constructors
RayHit::RayHit(const Vector3& point, const Vector3& normal, float distance) : point(point), normal(normal), distance(distance){}
RayHit::RayHit() : RayHit(Vector3(0), Vector3(0), std::numeric_limits<float>::infinity()){}

Ray::Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction.normalized()){}
Ray::Ray() : Ray(Vector3(0), Vector3(0)) {}

bool Ray::cast(const Shape& object, RayHit& hit) {
    bool isHit = object.intersectsWith(*this, hit);
    return isHit;
}

