#include "../include/headers.h"
#include "../include/Color.h"
#include "../include/Vector3.h"
#include "../include/Sphere.h"
#include "../include/Canvas.h"
#include "../include/Camera.h"
#include "../include/Plane.h"
#include "../include/Light.h"

#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <time.h>

void computePrimRay(int i, int j, Ray& ray, const Camera& camera);
Color traceRay(Ray& ray, const std::vector<Shape*>& objects);

int main(void){
    // Doing this to generate random spheres
    srand( (unsigned)time(NULL) );

    std::ofstream image;
    Canvas canvas(800, 600);
    Camera camera(Vector3(0, 0, -100), canvas, PI/4);

    std::vector<Shape*> objects;

    for(int i=0; i < 5; i++){
        objects.push_back(new Sphere(Vector3(rand()%50-25, 15, rand()%50-25), 5));
    }
    objects.push_back(new Plane(Vector3(0, 20, 0), Vector3(0, 1, 0)));

    image.open("image.ppm");
        image << "P6" << " " << canvas.width << " " << canvas.height << " 255" << std::endl;
        for(int i = 0; i < canvas.height; i++){
            for(int j = 0; j < canvas.width; j++){
                Ray primRay;
                computePrimRay(i, j, primRay, camera);
                Color pixelColor = traceRay(primRay, objects);
                image << pixelColor.r << pixelColor.g << pixelColor.b;
            }
        }
    image.close();
    for(int i=0; i < (int)objects.size() ; i++){
        delete objects[i];
    }
    return 0;
}

void computePrimRay(int i, int j, Ray& primRay, const Camera& camera){ 
    Canvas canvas = camera.canvas;
    Vector3 pixelPosition(j + 0.5f - canvas.width/2 + camera.position.x, 
                          i + 0.5f - canvas.height/2 - camera.position.y,
                          camera.focalLength);
    primRay.origin = camera.position;
    primRay.direction = (pixelPosition - camera.position).normalized();
}

Color traceRay(Ray& ray, const std::vector<Shape*>& objects){
    int n_objects = (int) objects.size();

    static Color backgroundColor(0, 0, 0);
    static Color shadowColor(0, 0, 0);

    static Light light(Vector3(1, 0, 0));

    RayHit hit(Vector3(0), Vector3(0), std::numeric_limits<float>::infinity());
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
    // render light
    Sphere lightSphere = Sphere(light.position, 1);
    isHit = ray.cast(lightSphere, hit);
    if(isHit){
        return light.color;
    }

    if (hit.distance == std::numeric_limits<float>::infinity())
        return backgroundColor;

    Ray shadowRay(hit.point, light.position - hit.point);
    for (int i = 0; i < n_objects; i++){
        isHit = shadowRay.cast(*objects[i], hit);
        if(isHit){
            return shadowColor;
        }
    }

    Vector3 point_light = (hit.point - light.position).normalized();
    float lightValue = std::max(Vector3::dot(point_light, hit.point), 0.0f);
    float lightIntensity = 5;
    char R = (char) lightValue * lightIntensity;
    char G = (char) lightValue * lightIntensity; 
    char B = (char) lightValue * lightIntensity;
    return Color(R, G, B);
}
