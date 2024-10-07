#ifndef VEC2_H
#define VEC2_H

#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y;
} V2;

V2 v2(float x, float y);
V2 v2v(float v);
V2 v2_add(V2 a, V2 b);
V2 v2_sub(V2 a, V2 b);
V2 v2_mul(V2 a, float v);
V2 v2_div(V2 a, float v);
double v2_mag(V2 a);
int v2_eq(V2 a, V2 b);
V2 v2_normalize(V2 a);

#ifdef VEC2_IMPLEMENTATION

V2 v2(float x, float y) {
    return (V2) { x, y };
}

V2 v2v(float v) {
    return v2(v, v);
}

V2 v2_add(V2 a, V2 b) {
    return v2(
            a.x + b.x,
            a.y + b.y
        );
}

V2 v2_sub(V2 a, V2 b) {
    return v2_add(a, v2_mul(b, -1));
}

V2 v2_mul(V2 a, float v) {
    return v2(a.x * v, a.y * v);
}

V2 v2_div(V2 a, float v) {
    if (v == 0) { abort(); }
    return v2_mul(a, (float) 1 / v);
}

double v2_mag(V2 a) {
    return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

int v2_eq(V2 a, V2 b) {
    return ((a.x == b.x) && (a.y == b.y));
}


V2 v2_normalize(V2 a) {
    if (v2_eq(a, v2v(0))) { abort(); }
    return v2_div(a, v2_mag(a));
}


#endif

#endif