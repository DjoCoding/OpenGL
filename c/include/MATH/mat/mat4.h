#ifndef MAT4_H
#define MAT4_H

#include <stdio.h>
#include <MATH/vec/vec3.h>
#include <MATH/mat/mat.h>

#define MAT4x4_ROWS 4
#define MAT4x4_COLS 4

typedef struct {
    float cs[MAT4x4_ROWS * MAT4x4_COLS];   // cs: co-efficients
} Mat4x4;

Mat4x4 mat4_init(float v);
Mat4x4 mat4_add(Mat4x4 a, Mat4x4 b);
Mat4x4 mat4_sub(Mat4x4 a, Mat4x4 b);
Mat4x4 mat4_smul(Mat4x4 a, float v);
Mat4x4 mat4_div(Mat4x4 a, float v);

Mat4x4 mat4_mul(Mat4x4 a, Mat4x4 b);

// TRANSFORMATIONS
Mat4x4 mat4_translation(V3 v);
Mat4x4 mat4_translate(Mat4x4 a, V3 v);

Mat4x4 mat4_rotation(float angle, V3 axis);
Mat4x4 mat4_rotate(Mat4x4 a, float angle, V3 axis);


Mat4x4 mat4_scaling(V3 s);
Mat4x4 mat4_scale(Mat4x4 a, V3 s);

#ifdef MAT4_IMPLEMENTATION

Mat4x4 mat4_init(float v) {
    Mat4x4 result = {0};

    for (size_t i = 0; i < MAT4x4_ROWS; ++i) {
        result.cs[GET_INDEX(i, i, MAT4x4_ROWS)] = v;
    }

    return result;
}

Mat4x4 mat4_add(Mat4x4 a, Mat4x4 b) {
    Mat4x4 result = a;

    for(size_t i = 0; i < MAT4x4_ROWS; ++i) {
        for(size_t j = 0; j < MAT4x4_COLS; ++j) {
            size_t index = GET_INDEX(i, j, MAT4x4_ROWS);
            result.cs[index] += b.cs[index]; 
        }
    }

    return result;
}

Mat4x4 mat4_sub(Mat4x4 a, Mat4x4 b) {
    return mat4_add(a, mat4_smul(b, -1));
}

Mat4x4 mat4_smul(Mat4x4 a, float v) {
    Mat4x4 result = a;
    for(size_t i = 0; i < MAT4x4_ROWS * MAT4x4_COLS; ++i) {
        result.cs[i] *= v;
    }
    return result;
}

Mat4x4 mat4_div(Mat4x4 a, float v) {
    return mat4_smul(a, (float) 1 / v);
}

Mat4x4 mat4_mul(Mat4x4 a, Mat4x4 b) {
    Mat4x4 result = {0};

    for(size_t i = 0; i < MAT4x4_ROWS; ++i) {
        for(size_t j = 0; j < MAT4x4_COLS; ++j) {
            float at_ij = 0;

            for(size_t k = 0; k < MAT4x4_COLS; ++k) {
                at_ij += a.cs[GET_INDEX(i, k, MAT4x4_ROWS)] * b.cs[GET_INDEX(k, i, MAT4x4_ROWS)];
            }
            
            result.cs[GET_INDEX(i, j, MAT4x4_ROWS)] = at_ij;      
        }  
    }

    return result;
}

Mat4x4 mat4_translation(V3 v) {
    Mat4x4 result = {0};

    result.cs[GET_INDEX(0, 0, MAT4x4_ROWS)] = 1;
    result.cs[GET_INDEX(0, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(0, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(0, 3, MAT4x4_ROWS)] = v.x;
    
    result.cs[GET_INDEX(1, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(1, 1, MAT4x4_ROWS)] = 1;
    result.cs[GET_INDEX(1, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(1, 3, MAT4x4_ROWS)] = v.y;
    
    result.cs[GET_INDEX(2, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(2, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(2, 2, MAT4x4_ROWS)] = 1;
    result.cs[GET_INDEX(2, 3, MAT4x4_ROWS)] = v.z;
    
    result.cs[GET_INDEX(3, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 3, MAT4x4_ROWS)] = 1;

    return result;
}

Mat4x4 mat4_translate(Mat4x4 a, V3 v) {
    return mat4_mul(mat4_translation(v), a);
}


Mat4x4 mat4_rotation(float angle, V3 axis) {
    // the unit vector of the axis
    V3 u = v3_normalize(axis);

    Mat4x4 result = {0};

    result.cs[GET_INDEX(0, 0, MAT4x4_ROWS)] = cosf(angle) + pow(u.x, 2) * (1 - cosf(angle));
    result.cs[GET_INDEX(0, 1, MAT4x4_ROWS)] = u.x * u.y * (1 - cosf(angle)) - u.z * sinf(angle);
    result.cs[GET_INDEX(0, 2, MAT4x4_ROWS)] = u.x * u.z * (1 - cosf(angle)) + u.y * sinf(angle);
    result.cs[GET_INDEX(0, 3, MAT4x4_ROWS)] = 0;
    
    result.cs[GET_INDEX(1, 0, MAT4x4_ROWS)] = u.y * u.x * (1 - cosf(angle)) + u.z * sinf(angle);
    result.cs[GET_INDEX(1, 1, MAT4x4_ROWS)] = cosf(angle) + pow(u.y, 2) * (1 - cosf(angle));
    result.cs[GET_INDEX(1, 2, MAT4x4_ROWS)] = u.y * u.z * (1 - cosf(angle)) - u.x * sinf(angle);
    result.cs[GET_INDEX(1, 3, MAT4x4_ROWS)] = 0;
    
    result.cs[GET_INDEX(2, 0, MAT4x4_ROWS)] = u.z * u.x * (1 - cosf(angle)) - u.y * sinf(angle);
    result.cs[GET_INDEX(2, 1, MAT4x4_ROWS)] = u.z * u.y * (1 - cosf(angle)) + u.x * sinf(angle);
    result.cs[GET_INDEX(2, 2, MAT4x4_ROWS)] = cosf(angle) + pow(u.z, 2) * (1 - cosf(angle));
    result.cs[GET_INDEX(2, 3, MAT4x4_ROWS)] = 0;
    
    result.cs[GET_INDEX(3, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 3, MAT4x4_ROWS)] = 1;

    return result;
}

Mat4x4 mat4_rotate(Mat4x4 a, float angle, V3 axis) {
    return mat4_mul(mat4_rotation(angle, axis), a);  
}


Mat4x4 mat4_scaling(V3 s) {
    Mat4x4 result = {0};

    result.cs[GET_INDEX(0, 0, MAT4x4_ROWS)] = s.x;
    result.cs[GET_INDEX(0, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(0, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(0, 3, MAT4x4_ROWS)] = 0;
    
    result.cs[GET_INDEX(1, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(1, 1, MAT4x4_ROWS)] = s.y;
    result.cs[GET_INDEX(1, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(1, 3, MAT4x4_ROWS)] = 0;
    
    result.cs[GET_INDEX(2, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(2, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(2, 2, MAT4x4_ROWS)] = s.z;
    result.cs[GET_INDEX(2, 3, MAT4x4_ROWS)] = 0;
    
    result.cs[GET_INDEX(3, 0, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 1, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 2, MAT4x4_ROWS)] = 0;
    result.cs[GET_INDEX(3, 3, MAT4x4_ROWS)] = 1;


    return result;
} 

Mat4x4 mat4_scale(Mat4x4 a, V3 s) {
    return mat4_mul(mat4_scaling(s), a);
}


#endif

#endif