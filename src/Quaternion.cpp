#include "../include/Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Quaternion::Quaternion() : Quaternion(0, 0, 0, 1) {}

Quaternion Quaternion::operator+(const Quaternion& other){
    Quaternion& a = (*this);
    const Quaternion& b = other;
    return Quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Quaternion Quaternion::operator-(const Quaternion& other){
    Quaternion& a = (*this);
    const Quaternion& b = other;
    return Quaternion(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

const float& Quaternion::operator[](uint8_t i) const{
    // actually w should be 0 index and x/y/z should be 1/2/3, but I won't bother with that
    return (&x)[i];
}
float& Quaternion::operator[](uint8_t i){
    return (&x)[i];
}

const float Quaternion::getMagnitude() const{
    const Quaternion& q = (*this);
    return sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

const Vector3 Quaternion::getEulerAngles() const{
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    const Quaternion& q = (*this);
    Vector3 angle;

    // roll (x-axis rotation)
    float sinr_cosp = 2* (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1- 2* (q.x * q.x + q.y * q.y);
    angle.x = atan2(sinr_cosp, cosr_cosp);

    // pitch (z-axis rotation)
    float siny_cosp = 2* (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1 - 2* (q.y * q.y + q.z * q.z);
    angle.z = atan2(siny_cosp, cosy_cosp);

    // yaw (y-axis rotation)
    float sinp = 2 * (q.w * q.y - q.z * q.x);
    if (abs(sinp) >= 1)
        angle.y = copysign(PI / 2, sinp);
    else
        angle.y = asin(sinp);

    return angle;
}

void Quaternion::setEulerAngles(const Vector3& angle){
    // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
    // yaw (Y), pitch (Z), roll(X)
    float yaw = angle.z;
    float pitch = angle.y;
    float roll = angle.x;

    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    Quaternion& q = (*this);
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;
}

void Quaternion::setEulerAngles(float x, float y, float z){ 
    Quaternion& q = (*this);
    q.setEulerAngles(Vector3(x, y, z));
}
