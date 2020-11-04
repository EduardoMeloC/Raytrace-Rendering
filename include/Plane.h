#pragma once

#include "headers.h"
#include "Shape.h"
#include "Ray.h"

class Plane: public Shape
{
public:
    Vector3 normal;

    //constructors
    Plane(const Vector3& position, Vector3 normal); 

    // virtual methods implementation
    RayHit* intersectsWith(const Ray& ray) const override;
};
