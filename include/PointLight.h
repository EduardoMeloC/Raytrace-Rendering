#pragma once

#include "Light.h"
// these are only being used to renderLight()
#include "Sphere.h"
#include "Ray.h"

class PointLight : public Light
{
public:
    //constructors 
    PointLight(const Vector3& position, const Color& color, float intensity);
    PointLight(const Vector3& position);

    //virtual methods implementation
    void getDirectionAndIntensity(const Vector3& pos, Vector3& lightDir, Vector3& lightIntensity) override;
    bool renderLight(Ray& ray, Vector3& color) override;
};
