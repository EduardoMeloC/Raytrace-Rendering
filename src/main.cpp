#include "../include/headers.h"
#include "../include/Vector3.h"
#include "../include/Sphere.h"
#include "../include/Canvas.h"
#include "../include/Camera.h"

#include <fstream>

int main(void){
    std::ofstream image;
    Canvas canvas(80, 60);
    Camera camera(canvas, PI/4);
    std::cout << camera.focalLength << std::endl;

    Sphere sphere(Vector3(0, 0, 100), 30);

    image.open("image.ppm");
        image << "P6" << " " << canvas.width << " " << canvas.height << " 255" << std::endl;
        for(int i = 0; i < canvas.height; i++){
            for(int j = 0; j < canvas.width; j++){
                Vector3 pixelPosition(j + 0.5f - canvas.width/2, i + 0.5f - canvas.height/2, camera.focalLength);
                Ray ray(camera.position, pixelPosition - camera.position);
                RayHit* hit = ray.cast(sphere);
                char R, G, B;
                R = (char) (255 * j / canvas.width);
                G = (char) (255 * i / canvas.height);
                B = (hit != nullptr) ? 255 : 0;
                image << R << G << B;
                if(hit) std::cout << "hit sphere!" << std::endl;
                delete hit;
            }
        }
    image.close();
    return 0;
}
