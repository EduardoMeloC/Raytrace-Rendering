#pragma once

#include "headers.h"
#include "Object.h"
#include "Ray.h"

class Sphere: public Object
{
public:
    float radius;

    //constructors
    Sphere(Vector3 position, float radius); 

    // virtual methods implementation
    RayHit* intersectsWith(const Ray& ray) const override;

private:
    float radius2;
};
