#include "../include/PointLight.h"

PointLight::PointLight(const Vector3& position, const Color& color, float intensity) : Light(position, color, intensity) {}
PointLight::PointLight(const Vector3& position) : Light(position) {}
