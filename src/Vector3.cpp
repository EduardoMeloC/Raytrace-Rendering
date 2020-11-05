#include "../include/Vector3.h"

Vector3 Vector3::operator+(const Vector3& other) const{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

bool Vector3::operator==(const Vector3& other) const{
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const{
    return !(*this == other);
}

Vector3& Vector3::operator += (const Vector3 &other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator -= (const Vector3 &other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator*(const float& value) const{
    return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator*(const Vector3& other) const{
    return Vector3::dot(*this, other);
}

Vector3 Vector3::operator/(const float& value) const{
    return Vector3(x / value, y / value, z / value);
}

const float& Vector3::operator[](uint8_t i) const{
    return (&x)[i];
}
float& Vector3::operator[](uint8_t i) {
    return (&x)[i];
}

// STATIC METHODS

float Vector3::dot(const Vector3& u, const Vector3& v){
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float Vector3::magnitude(const Vector3& v){
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Vector3::normalize(Vector3& v){
    v = v / magnitude(v);
    return v;
}

Vector3 Vector3::cross(const Vector3& u, const Vector3& v) {
    return Vector3(u.y*v.z - u.z*v.y,
                   u.z*v.x - u.x*v.z,
                   u.x*v.y - u.y*v.z);
}

// INSTANCE METHODS
float Vector3::dot(const Vector3& other) const{
    return dot(*this, other);
}

float Vector3::magnitude() const{
    return magnitude(*this);
}

Vector3 Vector3::normalized() const{
    Vector3 vec(this->x, this->y, this->z);
    vec = normalize(vec);
    return vec;
}

Vector3 Vector3::cross(const Vector3& other) const{
    return cross(*this, other);
}
