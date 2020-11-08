#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include "Color.h"

class Object
{
public:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    Matrix4x4 objectToWorld;

    // TODO: Separate classes for objects and transforms
    Color albedo;
    // constructors
    Object(const Vector3& position, const Quaternion& quaternion, const Vector3& scale, const Color& color);
    Object(const Vector3& position);
    Object();
    // destructors
    virtual ~Object() = 0;
    // methods
    void getObjectMatrix(Matrix4x4& m);
    void updateObjectMatrix(); // should be called after each transformation
};
