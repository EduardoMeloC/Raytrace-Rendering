#include "../include/Object.h"

Object::Object(float x, float y, float z) : position(x, y, z) {}
Object::Object(const Vector3& position): position(position) {}
