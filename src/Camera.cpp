#include "../include/Camera.h"

// constructor
Camera::Camera(Vector3 position, Canvas canvas, float fov) : position(position), canvas(canvas), fov(fov){
    focalLength = canvas.height / (2 * tan(fov/2 * PI));
}

Camera::Camera(Canvas canvas, float fov) : Camera::Camera(Vector3(0), canvas, fov) {}
    
