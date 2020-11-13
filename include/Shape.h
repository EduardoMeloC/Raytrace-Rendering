#pragma once

#include "Vector3.h"
#include "Object.h"

class Ray;
class RayHit;

enum class Material {diffuse, reflection, reflectionAndRefraction};

class Shape : public Object
{
public:
    Shape(const Vector3& position);
    Shape(const Vector3& position, const Color& albedo);
    Shape(const Vector3& position, const Color& albedo, const Material& material);
    virtual ~Shape() = 0;

    Color albedo = 255;
    float refractiveIndex = 1.3f;

    Material material;
    // virtual methods
    virtual bool intersectsWith(const Ray& ray, RayHit& hit) const = 0;
};
