#include "../include/Object.h"

Object::Object(const Vector3& position, const Quaternion& rotation, const Vector3& scale, const Color& albedo) : position(position), rotation(rotation), scale(scale), albedo(albedo) {
    updateObjectMatrix();
}

Object::Object(const Vector3& position) : Object::Object(position, Quaternion(), Vector3(1), Color(255)) {}
Object::Object() : Object::Object(Vector3(0)) {} 
Object::~Object() {}

void Object::getObjectMatrix(Matrix4x4& m){
    const float x = rotation.x, y = rotation.y, z = rotation.z, w = rotation.w;
    const float x2 = x+x, y2 = y+y, z2 = z+z;
    const float xx = x * x2, xy = x * y2,  xz = x * z2;
    const float yy = y * y2, yz = y * z2, zz = z * z2;
    const float wx = w * x2, wy = w * y2, wz = w * z2;

    const float sx = scale.x, sy = scale.y, sz = scale.z;
    
    // Assigning the first column
    m[0][0] = ( 1 - ( yy + zz ) ) * sx;
    m[1][0] = ( xy + wz ) * sx;
    m[2][0] = ( xz - wy ) * sx;
    m[3][0] = 0;
    // Assigning the second column
    m[0][1] = ( xy - wz ) * sy;
    m[1][1] = ( 1 - ( xx + zz ) ) * sy;
    m[2][1] = ( yz + wx ) * sy;
    m[3][1] = 0;
    // Assigning the third column
    m[0][2] = ( xz + wy ) * sz;
    m[1][2] = ( yz - wx ) * sz;
    m[2][2] = ( 1 - ( xx + yy ) ) * sz;
    m[3][2] = 0;
    // Assigning the fourth column
    m[0][3] = position.x;
    m[1][3] = position.y;
    m[2][3] = position.z;
    m[3][3] = 1;
}

void Object::updateObjectMatrix(){
    getObjectMatrix(objectToWorld);
}
