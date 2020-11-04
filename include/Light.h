#pragma once

#include "Vector3.h"
#include "Object.h" 
#include "Color.h"

class Light : public Object
{
public:
    Color color;

    //constructors 
    Light(const Vector3& position, const Color& color);
    Light(const Vector3& position);
};
