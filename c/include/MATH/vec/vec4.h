#ifndef VEC4_H
#define VEC4_H

#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y, z, w;
} V4;

V4 v4(float x, float y, float z, float w);
V4 v4v(float v);
V4 v4_add(V4 a, V4 b);
V4 v4_sub(V4 a, V4 b);
V4 v4_mul(V4 a, float v);
V4 v4_div(V4 a, float v);
double v4_mag(V4 a);
int v4_eq(V4 a, V4 b);
V4 v4_normalize(V4 a);
#ifdef VEC4_IMPLEMENTATION

V4 v4(float x, float y, float z, float w) {
    return (V4) { x, y, z, w };
}

V4 v4v(float v) {
    return v4(v, v, v, v);
}

V4 v4_add(V4 a, V4 b) {
    return v4(
            a.x + b.x,
            a.y + b.y,    
            a.z + b.z,
            a.w + a.w
        );
}

V4 v4_sub(V4 a, V4 b) {
    return v4_add(a, v4_mul(b, -1));
}

V4 v4_mul(V4 a, float v) {
    return v4(a.x * v, a.y * v, a.z * v, a.w * v);
}

V4 v4_div(V4 a, float v) {
    if (v == 0) { abort(); }
    return v4_mul(a, (float) 1 / v);
}

double v4_mag(V4 a) {
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
}

int v4_eq(V4 a, V4 b) {
    return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w)); 
}

V4 v4_normalize(V4 a) {
    if (v4_eq(a, v4v(0))) { abort(); }
    return v4_div(a, v4_mag(a));
}


#endif

#endif