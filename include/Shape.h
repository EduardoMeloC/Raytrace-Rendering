#pragma once

#include "Vector3.h"
#include "Object.h"

class Ray;
class RayHit;

class Shape : public Object
{
public:
    Shape(const Vector3& position);
    // virtual methods
    virtual RayHit* intersectsWith(const Ray& ray) const = 0;
};
