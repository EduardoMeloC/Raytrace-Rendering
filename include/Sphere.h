#pragma once

#include "headers.h"
#include "Shape.h"
#include "Ray.h"
#include "Color.h"

class Sphere: public Shape
{
public:
    float radius;

    //constructors
    Sphere(const Vector3& position, float radius); 

    //destructor
    ~Sphere();

    // virtual methods implementation
    bool intersectsWith(const Ray& ray, RayHit& hit) const override;

private:
    float radius2;
};
