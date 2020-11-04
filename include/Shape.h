#pragma once

#include "Vector3.h"
#include "Object.h"

class Ray;
class RayHit;

class Shape : public Object
{
public:
    Shape(const Vector3& position);
    virtual ~Shape() = 0;
    // virtual methods
    virtual bool intersectsWith(const Ray& ray, RayHit& hit) const = 0;
};
