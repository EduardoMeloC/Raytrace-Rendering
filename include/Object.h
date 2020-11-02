#pragma once

#include "Vector3.h"

class Ray;
class RayHit;

class Object
{
public:
    Vector3 position;

    // constructors
    Object(float x, float y, float z); 
    Object(const Vector3& position);

    // virtual methods
    virtual RayHit* intersectsWith(const Ray& ray) const = 0;
};
