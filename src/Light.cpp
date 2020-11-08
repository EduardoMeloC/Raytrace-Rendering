#include "../include/Light.h"

Light::Light(const Vector3& position, const Color& color, float intensity) : Object(position), color(color), intensity(intensity) {}
Light::Light(const Vector3& position) : Light(position, Color(255, 255, 255), 1) {}
Light::~Light(){}

bool Light::renderLight(Ray& ray, Vector3& color){return false;}
