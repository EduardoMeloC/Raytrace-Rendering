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

    static Light light(Vector3(1, 0, 0), Color(255, 0, 0));

    RayHit *closestHit = new RayHit(Vector3(0), Vector3(0), std::numeric_limits<float>::infinity());

    for (int i = 0; i < n_objects; i++){
        RayHit* hit = ray.cast(*objects[i]);
        if(hit){
            if(hit->distance < closestHit->distance){
                delete closestHit;
                closestHit = hit;
            }
            else{
                delete hit;
            }
        }
    }
    // render light
    Sphere lightSphere = Sphere(light.position, 1);
    RayHit* hit = ray.cast(lightSphere);
    if(hit){
        delete hit;
        return light.color;
    }

    if (closestHit->distance == std::numeric_limits<float>::infinity())
        return backgroundColor;

    Ray shadowRay(closestHit->point, light.position - closestHit->point);
    for (int i = 0; i < n_objects; i++){
        RayHit* hit = shadowRay.cast(*objects[i]);
        if(hit){
            delete hit;
            return shadowColor;
        }
    }

    float distanceToLight = (light.position - closestHit->point).magnitude();
    float maxDistance = 64; // this is the maximum distance still visible by light
    if(distanceToLight > maxDistance) distanceToLight = maxDistance;
    char R = (char) (255-(distanceToLight/maxDistance * 255)) * light.color.r;
    char G = (char) (255-(distanceToLight/maxDistance * 255)) * light.color.g;
    char B = (char) (255-(distanceToLight/maxDistance * 255)) * light.color.b;
    return Color(R, G, B);
}
