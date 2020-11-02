#include "../include/headers.h"
#include "../include/Vector3.h"
#include "../include/Sphere.h"

int main(void){
    Sphere sphere(Vector3(0, 3, 0), 1);
    Ray ray(Vector3(0, 0, 0), Vector3(0, 1, 0)); 

    RayHit* hit = ray.cast(sphere);

    std::cout << hit->point << std::endl;
    std::cout << hit->normal << std::endl;
    std::cout << hit->distance << std::endl;
    
    delete hit;

    return 0;
}
