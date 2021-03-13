//
// Created by duplex on 3/12/21.
//

#ifndef PROJECT_LIGHTBOARD_FASTMATH_H
#define PROJECT_LIGHTBOARD_FASTMATH_H


class fastMath {
    public:
        static float fastRangedLerp(int x, int y, int a);

        static float fastRangedLerp(long x, long y, long a);

        static float fastRangedLerp(float x, float y, float a);

        static float fastRangedLerp(double x, double y, double a);

        static int fastLog10 (int x);

        static int fastLog10 (long x);

        static int fastLog10 (float  x);

        static int fastLog10 (double x);

        static float fastLerp(int a, int b, float f);

        static float fastLerp(long a, long b, float f);

        static float fastLerp(float a, float b, float f);

        static float fastLerp(double a, double b, float f);
};


#endif //PROJECT_LIGHTBOARD_FASTMATH_H
