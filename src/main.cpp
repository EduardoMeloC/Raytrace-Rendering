#include "../include/headers.h"
#include "../include/Color.h"
#include "../include/Vector3.h"
#include "../include/Sphere.h"
#include "../include/Canvas.h"
#include "../include/Camera.h"
#include "../include/Plane.h"
#include "../include/PointLight.h"
#include "../include/DirectionalLight.h"
#include "../include/Quaternion.h"

#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <time.h>

void computePrimRay(int i, int j, Ray& ray, const Camera& camera);
Vector3 traceRay(Ray& ray, const std::vector<Shape*>& objects, const std::vector<Light*>& lights, const int& depth);

Vector3 refract(const Vector3& incidentRay, const Vector3& surfaceNormal, const float& refractiveIndex);
void fresnel(const Vector3& incidentRay, const Vector3& surfaceNormal, const float& refractiveIndex, float &kr);

// TODO: Camera LookAt
// TODO: Apply textures

#define MIRROR_SCENE

int main(void){
    // Image and Camera
    std::ofstream image;
    Canvas canvas(1280, 720);
    Camera camera(Vector3(0, 0, 0), canvas, 60);
    Vector3 *framebuffer = new Vector3[canvas.width * canvas.height];
    Vector3 *pixelColor = framebuffer;

    // Objects
    std::vector<Shape*> objects;
#ifdef RANDOM_SCENE
    for(int i=0; i < 5; i++){
        Vector3 randomPosition(randomFloat(-50, 50), 0, -randomFloat(-25, 25) + -75);
        for(int j=0; j < (int)objects.size(); j++){
            // avoid self intersection
            if((objects[j]->position - randomPosition).magnitude() < 10.f){
                randomPosition = Vector3(randomFloat(-50, 50), 0, -randomFloat(-25, 25) + -75);
                j=0;
            }
        }
        objects.push_back(new Sphere(randomPosition, 5));
        objects[i]->albedo = Color(randomFloat(0, 255), randomFloat(0, 255), randomFloat(0, 255));
    }
#endif
#ifndef RANDOM_SCENE
    int max_spheres = 10;
    for(int i=0; i < max_spheres; i++){
        Vector3 position(30 * cos(PI/max_spheres*i), 0, -30 * sin(PI/max_spheres*i) - 45);
        objects.push_back(new Sphere(position, 5));
        objects[i]->albedo = Color(randomFloat(0, 255), randomFloat(0, 255), randomFloat(0, 255));
    }
#endif
objects.push_back(new Sphere(Vector3(0, 0, -45), 5));
#ifdef MIRROR_SCENE
    objects.back()->material = Material::reflection;
#endif
#ifdef GLASS_SCENE
    objects.back()->material = Material::reflectionAndRefraction;
    objects.back()->refractiveIndex = 1.5f;
#endif
    objects.push_back(new Plane(Vector3(0, -5, 0), Vector3(0, 1, 0))); 

    // Lights
    std::vector<Light*> lights;
    lights.push_back(new PointLight(Vector3(-20, 20, -50), Color(255, 0, 255), 420));
    lights.push_back(new PointLight(Vector3(20, 20, -50), Color(0, 255, 255), 420));
    lights.push_back(new PointLight(Vector3(0, 20, -20*sqrt(3)), Color(255, 255, 205), 180));
    /* lights.push_back(new DirectionalLight(Vector3(0, -1, 0), Color(255), 0.03)); */
    /* lights.push_back(new DirectionalLight(Vector3(0, -1, -1), Color(255), 0.03)); */

    // Render on the frame buffer
    for(int i = 0; i < canvas.height; i++){
        for(int j = 0; j < canvas.width; j++){
            Ray primRay;
            computePrimRay(i, j, primRay, camera);
            *(pixelColor++) = traceRay(primRay, objects, lights, 4);
        }
    }

    // Write image to the output file
    image.open("image.ppm");
    image << "P6" << " " << canvas.width << " " << canvas.height << " 255" << std::endl;
    for(int i = 0; i < canvas.height * canvas.width; i++){
        char r = (char)(255 * my_clamp(0.f, 1.f, framebuffer[i].x));
        char g = (char)(255 * my_clamp(0.f, 1.f, framebuffer[i].y));
        char b = (char)(255 * my_clamp(0.f, 1.f, framebuffer[i].z));
        image << r << g << b;
    }
    image.close();

    // Free memory
    for(int i=0; i < (int)objects.size() ; i++){
        delete objects[i];
    }
    delete [] framebuffer;
    return 0;
}

void computePrimRay(int i, int j, Ray& primRay, const Camera& camera){ 
    Canvas canvas = camera.canvas;
    float imageAspectRatio = canvas.width / (float) canvas.height;
    // We'll calculate the pixel's world coordinate
    float pixelX = (2 * ((j + 0.5f) / (float)canvas.width) - 1) * tan(camera.fov/2 * PI/180) * imageAspectRatio;
    float pixelY = (1 - 2 * ((i + 0.5f) / (float)canvas.height)) * tan(camera.fov/2 * PI/180);

    primRay.origin = camera.position;
    primRay.direction = (Vector3(pixelX, pixelY, -1) - camera.position).normalized();
}

Vector3 traceRay(Ray& ray, const std::vector<Shape*>& objects, const std::vector<Light*>& lights, const int& depth){
    static float shadowBias = 1e-4;
    static int n_objects = (int) objects.size();
    static int n_lights = (int) lights.size();

    static Color backgroundColor(0, 0, 0);
    static Color shadowColor(0, 0, 0);

    RayHit hit;
    bool isHit;

    if(depth <= 0) return backgroundColor;

    for (int i = 0; i < n_objects; i++){
        RayHit closestHit;
        isHit = ray.cast(*objects[i], closestHit);
        if(isHit){
            if(closestHit.distance < hit.distance){
                hit = closestHit;
            }
        }
    }

    Vector3 hitColor(0);
    // render light (doesn't make too much sense, but it's nice to have)
    for(int i = 0; i < n_lights; i++){
        if(lights[i]->renderLight(ray, hitColor)) return hitColor;
    }

    if (hit.distance == std::numeric_limits<float>::infinity()){
        return backgroundColor;
    }


    switch(hit.hitObject->material){
        case Material::diffuse: {
            for(int i = 0; i < n_lights; i++){
                Light* light = lights[i];

                Vector3 shadowValue = Vector3(1);

                Vector3 lightDir, lightIntensity;
                light->getDirectionAndIntensity(hit.point, lightDir, lightIntensity);

                // Hard Shadow
                Ray shadowRay(hit.point + hit.normal * shadowBias, lightDir * -1);
                RayHit shadowHit;
                for (int i = 0; i < n_objects; i++){
                    isHit = shadowRay.cast(*objects[i], shadowHit);
                    // this if makes shadowRay's max length be the distance to light
                    if(shadowHit.distance > (light->position - shadowRay.origin).magnitude()) continue;
                    if(isHit){
                        shadowValue = static_cast<Vector3>(shadowColor) / 255;
                    }
                }
                float lightValue = std::max(hit.normal * (lightDir * -1), 0.f);
                Vector3 hitAlbedo = static_cast<Vector3>(hit.hitObject->albedo) / 255;
                hitColor.x += hitAlbedo.x / PI * lightIntensity.x * lightValue * shadowValue.x;
                hitColor.y += hitAlbedo.y / PI * lightIntensity.y * lightValue * shadowValue.y;
                hitColor.z += hitAlbedo.z / PI * lightIntensity.z * lightValue * shadowValue.z;
            }
            break;
        }
        case Material::reflection: {
            Vector3 reflectionOrig = hit.point + hit.normal * shadowBias;
            Vector3 reflectionDir = Vector3::reflect(ray.direction, hit.normal);
            Ray reflectionRay = Ray(reflectionOrig, reflectionDir);
            hitColor += traceRay(reflectionRay, objects, lights, depth - 1) * powf(0.8f, n_lights);
            break;
        }
        case Material::reflectionAndRefraction: {
            // I must confess I don't quite understand this part
            Vector3 refractionColor = 0, reflectionColor = 0;
            float kr;
            fresnel(ray.direction, hit.normal, hit.hitObject->refractiveIndex, kr);
            bool isOutside = ray.direction.dot(hit.normal) < 0;
            Vector3 bias = hit.normal * shadowBias;
            // compute refraction if it's not a case of internal reflection
            if(kr < 1) {
                Vector3 refractionDirection = refract(ray.direction, hit.normal, hit.hitObject->refractiveIndex).normalized();
                Vector3 refractionRayOrig = isOutside ? hit.point - bias : hit.point + bias;
                Ray refractionRay(refractionRayOrig, refractionDirection);
                refractionColor = traceRay(refractionRay, objects, lights, depth-1);
            }
            Vector3 reflectionDirection = Vector3::reflect(ray.direction, hit.normal).normalized();
            Vector3 reflectionRayOrig = isOutside ? hit.point + bias : hit.point - bias;
            Ray reflectionRay(reflectionRayOrig, reflectionDirection);
            reflectionColor = traceRay(reflectionRay, objects, lights, depth-1);

            hitColor += reflectionColor * kr + refractionColor * (1 - kr);
            break;      
        }
    }
    return hitColor;
}

Vector3 refract(const Vector3& incidentRay, const Vector3& surfaceNormal, const float& refractiveIndex){
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel 
    Vector3 N = surfaceNormal;
    float cosi = my_clamp(-1, 1, N * incidentRay);
    float fromRefr = 1, toRefr = refractiveIndex; // fromRefr is the index of refraction of the refractive index of the medium the ray comes from, and toRefr the index of refraction the ray is going to
    if (cosi < 0){
        // outside the surface
        cosi = -cosi;
    }
    else {
        // inside the surface
        N = surfaceNormal * -1;
        std::swap(fromRefr, toRefr);
    }
    float Refr = fromRefr / toRefr;
    
    // check for total internal reflection
    float k = 1 - Refr * Refr * (1 - cosi * cosi);
    return k < 0 ? 0 : incidentRay * Refr + N * (Refr * cosi - sqrtf(k));
}

void fresnel(const Vector3& incidentRay, const Vector3& surfaceNormal, const float& refractiveIndex, float &kr){
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
    float cosi = my_clamp(-1, 1, surfaceNormal * incidentRay);
    float fromRefr = 1, toRefr = refractiveIndex;
    if (cosi > 0) { std::swap(fromRefr, toRefr); }
    // Compute sini angle using Snell's law
    float sint = fromRefr / toRefr * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if(sint >= 1){
        kr = 1;
        std::cout << "Total internal reflection" << std::endl;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((toRefr * cosi) - (fromRefr * cost)) / ((toRefr * cosi) + (fromRefr * cost));
        float Rp = ((fromRefr * cosi) - (toRefr * cost)) / ((fromRefr * cosi) + (toRefr * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
}
