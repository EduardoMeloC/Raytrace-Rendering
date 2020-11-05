#pragma once
#include "headers.h"
#include "Vector3.h"

struct Matrix4x4
{
    // https://www.scratchapixel.com/code.php?id=26&origin=/lessons/3d-basic-rendering/rasterization-practical-implementation&src=2
    float m[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    // constructors
    Matrix4x4();
    Matrix4x4 (float v00, float v01, float v02, float v03,
              float v10, float v11, float v12, float v13,
              float v20, float v21, float v22, float v23,
              float v30, float v31, float v32, float v33);

    // access operators
    // these allow you to write mat[0][3] = 1.f instead of mat.m[0][3] = 1.f
    const float* operator[](uint8_t i) const;
    float* operator[](uint8_t i);
    
    // methods
    Matrix4x4 operator * (const Matrix4x4& other) const;
    Matrix4x4 transpose() const;
    void multPointMatrix(const Vector3& src, Vector3& dst) const;
    void multVectorMatrix(const Vector3& src, Vector3& dst) const;
    Matrix4x4 inverse() const;
    const Matrix4x4& invert();
};


