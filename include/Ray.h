#pragma once

#include "headers.h"
#include "Vector3.h"
#include "Object.h"

struct RayHit
{
    friend struct Ray;
    friend class Sphere;

    Vector3 point;
    Vector3 normal;
    float distance;

protected:
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
   RayHit* cast(const Object& object);
};
