#pragma once

#include "headers.h"
#include "Shape.h"
#include "Ray.h"

class Sphere: public Shape
{
public:
    float radius;

    //constructors
    Sphere(const Vector3& position, float radius); 

    // virtual methods implementation
    RayHit* intersectsWith(const Ray& ray) const override;

private:
    float radius2;
};
