#pragma once

#include "headers.h"
#include "Vector3.h"
#include "Shape.h"

struct RayHit
{
    Vector3 point;
    Vector3 normal;
    float distance;

    RayHit(const Vector3& point, const Vector3& normal, float distance);
};

struct Ray
{
    Vector3 origin;
    Vector3 direction;

    // constructors
    Ray(const Vector3& origin, const Vector3& direction);
    Ray();

    // methods
   RayHit* cast(const Shape& object);
};
