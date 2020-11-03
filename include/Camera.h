#pragma once
#include "headers.h"
#include "Vector3.h"
#include "Canvas.h"

class Camera{
public:
    Vector3 position;
    Canvas canvas;
    float fov; // vertical fov
    float focalLength;

    Camera(Vector3 position, Canvas canvas, float fov);
    Camera(Canvas canvas, float fov);
};
