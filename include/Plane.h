#pragma once

#include "headers.h"
#include "Object.h"
#include "Ray.h"

class Plane: public Object
{
public:
    Vector3 normal;

    //constructors
    Plane(Vector3 position, Vector3 normal); 

    // virtual methods implementation
    RayHit* intersectsWith(const Ray& ray) const override;
};
