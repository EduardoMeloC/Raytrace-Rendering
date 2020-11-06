#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
    //constructors 
    DirectionalLight(const Vector3& direction, const Color& color, float intensity);
    DirectionalLight(const Vector3& direction);

    Vector3 direction;
};
