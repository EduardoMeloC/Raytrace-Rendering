#pragma once
#include "headers.h"
#include "Vector3.h"

struct Color{
    // each value ranges from 0 to 255
    unsigned char r, g, b;

    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(unsigned char value);

    //cast to vector3
    operator Vector3() const;
};

// to string
inline std::ostream& operator<<(std::ostream& Str, Color const& v){
    Str << "(" << +v.r << ", " << +v.g << ", " << +v.b << ")";
    return Str;
}
