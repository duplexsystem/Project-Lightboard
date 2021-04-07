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

float fastMath :: fastRangedLerp(double x, double y, double a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(getDigitsInNumber(a)+1)]));
    return fastLerp(x, y, rangedPram);
}

float fastMath :: fastRangedLerp(float x, float y, float a) {
    float rangedPram = ((static_cast<float>(a))/(consts::pow10[(getDigitsInNumber(a)+1)]));
    return fastLerp(x, y, rangedPram);
}


int fastMath :: getDigitsInNumber (long x) {
    int z = (((consts::longsize) - (__builtin_clzl(x))) / 0x3.5269E12F346E2886177Fp0f) + 1;
    return z + (1 ^ ((unsigned int)(x - consts::pow10[z]) >> (consts::longsize - 1)));
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

//static int highestOneBit(int i) {
//    i |= (i >>  1);
//    i |= (i >>  2);
//    i |= (i >>  4);
//    i |= (i >>  8);
//    i |= (i >> 16);
//    return i - ((unsigned)i >> 1);
//}
//
//long fastMath :: invert_bit(long n){
//    long x = log2(n) ;
//    long m = 1 << x;
//    m = m | m - 1;
//    n = n ^ m;
//    return n;
//}


