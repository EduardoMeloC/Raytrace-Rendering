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

float my_clamp(float min, float max, const float& value);

void computePrimRay(int i, int j, Ray& ray, const Camera& camera);
Vector3 traceRay(Ray& ray, const std::vector<Shape*>& objects, const std::vector<Light*>& lights);

int main(void){
    // Doing this to generate random spheres
    srand( (unsigned)time(NULL) );

    std::ofstream image;
    Canvas canvas(1280, 720);
    Camera camera(Vector3(0, 0, 0), canvas, 60);

    Vector3 *framebuffer = new Vector3[canvas.width * canvas.height];
    Vector3 *pixelColor = framebuffer;
    std::vector<Shape*> objects;

    for(int i=0; i < 5; i++){
        objects.push_back(new Sphere(Vector3(rand()%100-50, 0, -(rand()%100-50)-60), 5));
        objects[i]->albedo = Color(rand()%255, rand()%255, rand()%255);
    }
    objects.push_back(new Plane(Vector3(0, -5, 0), Vector3(0, 1, 0))); 
    /* objects.push_back(new Plane(Vector3(-20, 0, 0), Vector3(1, 0, 0))); */ 

    std::vector<Light*> lights;
    lights.push_back(new PointLight(Vector3(-20, 20, -50), Color(255, 0, 255), 120));
    lights.push_back(new PointLight(Vector3(20, 20, -50), Color(0, 255, 255), 120));
    /* lights.push_back(new DirectionalLight(Vector3(-0.5, -1, -1), Color(255), 0.1)); */

    for(int i = 0; i < canvas.height; i++){
        for(int j = 0; j < canvas.width; j++){
            Ray primRay;
            computePrimRay(i, j, primRay, camera);
            *(pixelColor++) = traceRay(primRay, objects, lights);
        }
    }

    image.open("image.ppm");
    image << "P6" << " " << canvas.width << " " << canvas.height << " 255" << std::endl;
    for(int i = 0; i < canvas.height * canvas.width; i++){
        char r = (char)(255 * my_clamp(0.f, 1.f, framebuffer[i].x));
        char g = (char)(255 * my_clamp(0.f, 1.f, framebuffer[i].y));
        char b = (char)(255 * my_clamp(0.f, 1.f, framebuffer[i].z));
        image << r << g << b;
    }
    image.close();

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

Vector3 traceRay(Ray& ray, const std::vector<Shape*>& objects, const std::vector<Light*>& lights){
    static float shadowBias = 1e-4;
    static int n_objects = (int) objects.size();
    static int n_lights = (int) lights.size();

    static Color backgroundColor(0, 0, 0);
    static Color shadowColor(0, 0, 0);

    RayHit hit;
    bool isHit;

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

    if (hit.distance == std::numeric_limits<float>::infinity())
        return backgroundColor;

    for(int i = 0; i < n_lights; i++){
        Light* light = lights[i];

        Vector3 shadowValue = Vector3(1);

        Vector3 lightDir, lightIntensity;
        light->getDirectionAndIntensity(hit.point, lightDir, lightIntensity);

        Ray shadowRay(hit.point + hit.normal * shadowBias, lightDir * -1);
        RayHit shadowHit;
        for (int i = 0; i < n_objects; i++){
            isHit = shadowRay.cast(*objects[i], shadowHit);
            // this if makes shadowRay's max length be the distance to light
            if(shadowHit.distance > (light->position - shadowRay.origin).magnitude()) continue;
            if(isHit){
                /* std::cout << "returning shadow" << std::endl; */
                shadowValue = static_cast<Vector3>(shadowColor) / 255;
            }
        }

        /* Vector3 pointToLight = (light->position - hit.point).normalized(); */
        /* std::cout << lightDir << std::endl << lightIntensity << std::endl; */
        /* float lightValue = std::max(Vector3::dot(pointToLight, hit.normal), 0.0f); */
        float lightValue = std::max(hit.normal * (lightDir * -1), 0.f);
        Vector3 hitAlbedo = static_cast<Vector3>(hit.hitObject->albedo) / 255;
        /* Vector3 lightColor = static_cast<Vector3>(light->color) / 255; */
        /* float R = lightValue * lightIntensity / (4 * PI * pointLightRadius * pointLightRadius); */
        /* float G = lightValue * lightIntensity / (4 * PI * pointLightRadius * pointLightRadius); */
        /* float B = lightValue * lightIntensity / (4 * PI * pointLightRadius * pointLightRadius); */
        /* std::cout << "returning object's color: " << Vector3(R, G, B) << std::endl; */
        hitColor.x += hitAlbedo.x / PI * lightIntensity.x * lightValue * shadowValue.x;
        hitColor.y += hitAlbedo.y / PI * lightIntensity.y * lightValue * shadowValue.y;
        hitColor.z += hitAlbedo.z / PI * lightIntensity.z * lightValue * shadowValue.z;

        /* std::cout << Vector3(R, G, B) << std::endl; */
    }

    return hitColor;
}

float my_clamp(float min, float max, const float& value){
    float clamped = value;
    if(clamped < min) clamped = min;
    if(clamped > max) clamped = max;
    return clamped;
}
