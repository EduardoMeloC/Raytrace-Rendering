#pragma once

#include "headers.h"
#include "Vector3.h"
#include "Shape.h"

#include <limits>

struct RayHit
{
    const Shape* hitObject;
    Vector3 point;
    Vector3 normal;
    float distance;

    RayHit(const Vector3& point, const Vector3& normal, float distance, const Shape* hitObject);
    RayHit();
};

struct Ray
{
    Vector3 origin;
    Vector3 direction;

    // constructors
    Ray(const Vector3& origin, const Vector3& direction);
    Ray();

    // methods
    bool cast(const Shape& object, RayHit& hit);
};
