#pragma once 
#include "headers.h"
#include "Vector3.h"

struct Quaternion{
    float x, y, z, w;

    Quaternion(float x, float y, float z, float w);
    Quaternion();


    Quaternion operator+(const Quaternion& other);
    Quaternion operator-(const Quaternion& other);
    const float& operator[](uint8_t i) const;
    float& operator[](uint8_t i);
    const float getMagnitude() const;
    const Vector3 getEulerAngles() const;
    void setEulerAngles(const Vector3& angle);
    void setEulerAngles(float x, float y, float z);
};

// to string
inline std::ostream& operator<<(std::ostream& Str, Quaternion const& q){
    Str << "(" << q.w << ", " << q.x << ", " << q.y <<  ", " << q.z << ")";
    return Str;
} 
