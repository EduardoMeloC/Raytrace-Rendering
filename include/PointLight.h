#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
    //constructors 
    PointLight(const Vector3& position, const Color& color, float intensity);
    PointLight(const Vector3& position);
};
