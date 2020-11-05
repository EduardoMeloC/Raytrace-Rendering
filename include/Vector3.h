#pragma once

#include "headers.h"

struct Vector3
{
    float x, y, z;

    // constructors
    Vector3(float x, float y, float z) : x(x), y(y), z(z){}
    Vector3(float value) : Vector3(value, value, value){}
    Vector3() : Vector3(0){}

    // operator functions
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3 operator*(const float& value) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator/(const float& value) const;

    // acess operators
    const float& operator[](uint8_t i) const;
    float& operator[](uint8_t i);

    // static methods
    static float dot(const Vector3& u, const Vector3& v);
    static float magnitude(const Vector3& v);
    static Vector3 normalize(Vector3& v); // makes the vector normalized
    static Vector3 cross(const Vector3& u, const Vector3& v);

    // instance methods
    float dot(const Vector3& other) const;
    float magnitude() const;
    Vector3 normalized() const; // returns a new normalized vector
    Vector3 cross(const Vector3& other) const;

};

// to string
inline std::ostream& operator<<(std::ostream& Str, Vector3 const& v){
    Str << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return Str;
} 
