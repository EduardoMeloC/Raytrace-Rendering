#include "../include/DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3& direction, const Color& color, float intensity) : Light(Vector3(0), color, intensity), direction(direction) {}
DirectionalLight::DirectionalLight(const Vector3& direction) : Light(Vector3(0)), direction(direction) {}
