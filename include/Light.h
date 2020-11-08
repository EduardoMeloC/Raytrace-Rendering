#pragma once

#include "Vector3.h"
#include "Object.h" 
#include "Color.h"
#include "Ray.h"

class Light : public Object
{
public:
    Color color;
    float intensity;

    //constructors 
    Light(const Vector3& position, const Color& color, float intensity);
    Light(const Vector3& position);
    //destructor
    virtual ~Light() = 0;

    virtual void getDirectionAndIntensity(const Vector3& pos, Vector3& lightDir, Vector3& lightIntensity) = 0;
    virtual bool renderLight(Ray& ray, Vector3& color); // this is a horrible name for the method
};
