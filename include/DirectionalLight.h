#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
    Vector3 direction;

    //constructors 
    DirectionalLight(const Vector3& direction, const Color& color, float intensity);
    DirectionalLight(const Vector3& direction);

    //virtual methods implementation
    void getDirectionAndIntensity(const Vector3& pos, Vector3& lightDir, Vector3& lightIntensity) override;
};
