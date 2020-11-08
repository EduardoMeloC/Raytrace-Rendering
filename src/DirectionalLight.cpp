#include "../include/DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3& direction, const Color& color, float intensity) : Light(Vector3(0), color, intensity), direction(direction.normalized()) {}
DirectionalLight::DirectionalLight(const Vector3& direction) : Light(Vector3(0)), direction(direction) {}

void DirectionalLight::getDirectionAndIntensity(const Vector3& pos, Vector3& lightDir, Vector3& lightIntensity){
    // pos is the position of the shaded point
    lightDir = direction;
    lightIntensity = static_cast<Vector3>(color)/255;
}
