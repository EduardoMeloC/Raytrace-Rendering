#include "../include/headers.h"
#include "../include/Color.h"
#include "../include/Vector3.h"
#include "../include/Sphere.h"
#include "../include/Canvas.h"
#include "../include/Camera.h"

#include <fstream>

void computePrimRay(int i, int j, Ray& ray, const Camera& camera);

int main(void){
    std::ofstream image;
    Canvas canvas(800, 600);
    Camera camera(canvas, PI/4);
    Color backgroundColor(0, 0, 0);

    Sphere sphere(Vector3(0, 0, 100), 30);

    image.open("image.ppm");
        image << "P6" << " " << canvas.width << " " << canvas.height << " 255" << std::endl;
        for(int i = 0; i < canvas.height; i++){
            for(int j = 0; j < canvas.width; j++){
                Ray primRay;
                computePrimRay(i, j, primRay, camera);
                RayHit* hit = primRay.cast(sphere);
                Color pixelColor = backgroundColor;
                if(hit){
                    pixelColor.r = (char) (255 * j / canvas.width);
                    pixelColor.g = (char) (255 * i / canvas.height);
                    pixelColor.b = 255;
                }
                image << pixelColor.r << pixelColor.g << pixelColor.b;
                delete hit;
            }
        }
    image.close();
    return 0;
}

void computePrimRay(int i, int j, Ray& primRay, const Camera& camera){ 
    Canvas canvas = camera.canvas;
    Vector3 pixelPosition(j + 0.5f - canvas.width/2, i + 0.5f - canvas.height/2, camera.focalLength);
    primRay.origin = camera.position;
    primRay.direction = (pixelPosition - camera.position).normalized();
}
