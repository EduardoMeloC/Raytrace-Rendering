#include "../include/Color.h"

Color::Color(char r, char g, char b) : r(r), g(g), b(b) {}

Color::operator Vector3() const{
    return Vector3(r, g, b);
}

