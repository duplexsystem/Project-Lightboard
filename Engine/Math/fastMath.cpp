//
// Created by duplex on 3/12/21.
//

#include <iostream>
#include "fastMath.h"
#include "consts.h"
#include <climits>
#include <bitset>
#include <bits/stdc++.h>

float fastMath :: fastRangedLerp(int x, int y, int a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(getDigitsInNumber(a)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(long x, long y, long a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(getDigitsInNumber(a)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(float x, float y, float a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(getDigitsInNumber((int)a)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(double x, double y, double a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(getDigitsInNumber((long)a)+1)]));
    return fastLerp(x, y, rangedPram);
}

int fastMath :: getDigitsInNumber (int x) {
    int maxdigits = ((consts::intsize - __builtin_clz(x)) / 0x3.5269E12F346E2886177Fp0f) + 1;
    return maxdigits - __builtin_signbitl(x - consts::pow10[maxdigits]);
}

long fastMath :: getDigitsInNumber (long x) {
    long mindigits = (consts::longsize - __builtin_clzl(x)) / 0x3.5269E12F346E2886177Fp0f;
    return mindigits + __builtin_signbitl(consts::pow10[mindigits] - x);
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
