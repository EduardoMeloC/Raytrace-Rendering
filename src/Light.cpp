#include "../include/Light.h"

Light::Light(const Vector3& position, const Color& color) : Object(position), color(color) { std::cout << color << std::endl; }
Light::Light(const Vector3& position) : Light(position, Color(255, 255, 255)) {}
