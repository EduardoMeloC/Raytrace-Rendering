#include "../include/headers.h"
#include "../include/Vector3.h"
#include "../include/Sphere.h"

#include <fstream>

int main(void){
    std::ofstream image;
    const uint16_t image_width = 80;
    const uint16_t image_height = 60;

    image.open("image.ppm");
        image << "P3" << " " << image_width << " " << image_height << " 255" << std::endl;
        for(uint16_t i = 0; i < image_height; i++){
            for(uint16_t j = 0; j < image_width; j++){
                int R, G, B;
                R = (int) (255 * j / image_width);
                G = (int) (255 * i / image_height);
                B = 0;
                image << R << " " << G << " " << B << "\t";
            }
            image << std::endl;
        }
    image.close();
    return 0;
}
