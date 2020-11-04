#pragma once
#include "headers.h"

struct Color{
    // each value ranges from 0 to 255
    char r, g, b;

    Color(char r, char g, char b);
};

// to string
inline std::ostream& operator<<(std::ostream& Str, Color const& v){
    Str << "(" << +v.r << ", " << +v.g << ", " << +v.b << ")";
    return Str;
}
