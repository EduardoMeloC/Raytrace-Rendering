#pragma once

#include <iostream>
#include <math.h>
#include <stdint.h>
#include <random>

#define PI 3.14159265

inline float randomFloat(float min, float max){
    static std::uniform_real_distribution<float> distribution(min, max);
    static std::mt19937 generator{ std::random_device()() };
    return distribution(generator);
}

inline float randomFloat(){
    return randomFloat(0.f, 1.f);
}

inline float my_clamp(float min, float max, const float& value){
    float clamped = value;
    if(clamped < min) clamped = min;
    if(clamped > max) clamped = max;
    return clamped;
}
