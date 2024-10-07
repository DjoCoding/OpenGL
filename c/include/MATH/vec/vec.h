#ifndef VEC_H
#define VEC_H

#include <MATH/vec/vec4.h>
#include <MATH/vec/vec3.h>
#include <MATH/vec/vec2.h>

V4 v4_from_v2(V2 a, float z, float w);
V4 v4_from_v3(V2 a, float w);
V3 v3_from_v2(V2 a, float z);
V3 v3_from_v4(V4 a);
V2 v2_from_v3(V3 a);
V2 v2_from_v4(V4 a);

#ifdef VEC_IMPLEMENTATION

V4 v4_from_v2(V2 a, float z, float w) {
    return v4(a.x, a.y, z, w);
}

V4 v4_from_v3(V2 a, float w) {
    return v4(a.x, a.y, a.z, w);
}

V3 v3_from_v2(V2 a, float z) {
    return v3(a.x, a.y, z);
}

V3 v3_from_v4(V4 a) {
    return v3(a.x, a.y, a.z);
}

V2 v2_from_v4(V4 a) {
    return v2(a.x, a.y);
}

V2 v2_from_v3(V3 a) {
    return v2(a.x, a.y);
}

#endif

#endif