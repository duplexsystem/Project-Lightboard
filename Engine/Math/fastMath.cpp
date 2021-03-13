//
// Created by duplex on 3/12/21.
//

#include "fastMath.h"
#include "consts.h"*

float fastMath :: fastRangedLerp(int x, int y, int a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(fastLog10(a)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(long x, long y, long a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(fastLog10(a)+1)]) + ((static_cast<float>(a)/10000000000000000000)/10));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(double x, double y, double a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(fastLog10(a)+1)]) + ((static_cast<float>(a)/10000000000000000000)/10));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(float x, float y, float a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(fastLog10(a)+1)]) + ((static_cast<float>(a)/10000000000000000000)/10));
    return fastLerp(x, y, rangedPram);
}

int fastMath :: fastLog10 (int x) {
    int i = 0;
    while(x > 9) {
        x/=10;
        i++;
    }
    return i;
}

int fastMath :: fastLog10 (long x) {
    int i = 0;
    while(x > 9) {
        x/=10;
        i++;
    }
    return i;
}

int fastMath :: fastLog10 (double x) {
    int i = 0;
    while(x > 9) {
        x/=10;
        i++;
    }
    return i;
}

int fastMath :: fastLog10 (float x) {
    int i = 0;
    while(x > 9) {
        x/=10;
        i++;
    }
    return i;
}

float fastMath :: fastLerp(int a, int b, float f) {
    return a + f * (b - a);
}

float fastMath :: fastLerp(long a, long b, float f) {
    return a + f * (b - a);
}

float fastMath :: fastLerp(double a, double b, float f) {
    return a + f * (b - a);
}

float fastMath :: fastLerp(float a, float b, float f) {
    return a + f * (b - a);
}

