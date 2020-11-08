#include "../include/PointLight.h"

PointLight::PointLight(const Vector3& position, const Color& color, float intensity) : Light(position, color, intensity) {}
PointLight::PointLight(const Vector3& position) : Light(position) {}

void PointLight::getDirectionAndIntensity(const Vector3& pos, Vector3& lightDir, Vector3& lightIntensity){
    // pos is the position of the shaded point
    lightDir = pos - position;
    float r2 = lightDir.magnitude();
    Vector3::normalize(lightDir);
    lightIntensity = static_cast<Vector3>(color)/255 * intensity / (4 * PI * r2);
}

bool PointLight::renderLight(Ray& ray, Vector3& color){
    Sphere lightSphere = Sphere(position, 1);

    RayHit hit;
    bool isHit = ray.cast(lightSphere, hit);
    if(isHit){
        color = static_cast<Vector3>((*this).color)/255;
    }
    return isHit;
}
