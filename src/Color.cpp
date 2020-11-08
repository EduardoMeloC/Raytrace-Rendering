#include "../include/Color.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
Color::Color(unsigned char value) : Color(value, value, value) {}

Color::operator Vector3() const{
    return Vector3(r, g, b);
}

