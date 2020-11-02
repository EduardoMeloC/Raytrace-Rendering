#include "../include/Ray.h"

// constructors
RayHit::RayHit(const Vector3& point, const Vector3& normal, float distance) : point(point), normal(normal), distance(distance){}
Ray::Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction.normalized()){}

RayHit* Ray::cast(const Object& object) {
    RayHit* hit = object.intersectsWith(*this);
    return hit;
}

