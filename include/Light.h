#pragma once

#include "Vector3.h"
#include "Object.h" 
#include "Color.h"

class Light : public Object
{
public:
    Color color;
    float intensity;

    //constructors 
    Light(const Vector3& position, const Color& color, float intensity);
    Light(const Vector3& position);
    //destructor
    virtual ~Light();
};
