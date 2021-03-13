//
// Created by duplex on 3/12/21.
//

#include "fastMath.h"
#include "consts.h"*

float fastMath :: fastRangedLerp(int x, int y, int a) {
    double xx = x >= 0 ? x * 2 : x * -2 - 1;
    double yy = y >= 0 ? y * 2 : y * -2 - 1;
    double key = ((xx >= yy) ? (xx * xx + xx + yy) : (yy * yy + xx)+a);
    float rangedPram = ((static_cast<float>(key))/(consts::pow10[(fastLog10(key)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(long x, long y, long a) {
    double xx = x >= 0 ? x * 2 : x * -2 - 1;
    double yy = y >= 0 ? y * 2 : y * -2 - 1;
    double key = ((xx >= yy) ? (xx * xx + xx + yy) : (yy * yy + xx)+a);
    float rangedPram = ((static_cast<float>(key))/(consts::pow10[(fastLog10(key)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(double x, double y, double a) {
    double xx = x >= 0 ? x * 2 : x * -2 - 1;
    double yy = y >= 0 ? y * 2 : y * -2 - 1;
    double key = ((xx >= yy) ? (xx * xx + xx + yy) : (yy * yy + xx)+a);
    float rangedPram = ((static_cast<float>(key))/(consts::pow10[(fastLog10(key)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(float x, float y, float a) {
    double xx = x >= 0 ? x * 2 : x * -2 - 1;
    double yy = y >= 0 ? y * 2 : y * -2 - 1;
    double key = ((xx >= yy) ? (xx * xx + xx + yy) : (yy * yy + xx)+a);
    float rangedPram = ((static_cast<float>(key))/(consts::pow10[(fastLog10(key)+1)]));
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

