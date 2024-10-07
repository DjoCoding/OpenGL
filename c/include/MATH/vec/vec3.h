#ifndef VEC3_H
#define VEC3_H

#include <stdlib.h>
#include <math.h>


typedef struct {
    float x, y, z;
} V3;

V3 v3(float x, float y, float z);
V3 v3v(float v);
V3 v3_add(V3 a, V3 b);
V3 v3_sub(V3 a, V3 b);
V3 v3_mul(V3 a, float v);
V3 v3_div(V3 a, float v);
double v3_mag(V3 a);
int v3_eq(V3 a, V3 b);
V3 v3_normalize(V3 a);

#ifdef VEC3_IMPLEMENTATION

V3 v3(float x, float y, float z) {
    V3 v = {0};
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
    // return (V3) { x, y, z };
}

V3 v3v(float v) {
    return v3(v, v, v);
}

V3 v3_add(V3 a, V3 b) {
    return v3(
            a.x + b.x,
            a.y + b.y,    
            a.z + b.z
        );
}

V3 v3_sub(V3 a, V3 b) {
    return v3_add(a, v3_mul(b, -1));
}

V3 v3_mul(V3 a, float v) {
    return v3(a.x * v, a.y * v, a.z * v);
}

V3 v3_div(V3 a, float v) {
    if (v == 0) { abort(); }
    return v3_mul(a, (float) 1 / v);
}

double v3_mag(V3 a) {
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

int v3_eq(V3 a, V3 b) {
    return ((a.x == b.x) && (a.y == b.y) && (a.z == a.z));
}

V3 v3_normalize(V3 a) {
    if (v3_eq(a, v3v(0))) { abort(); }
    return v3_div(a, v3_mag(a));
}


#endif

#endif