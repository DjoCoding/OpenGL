#ifndef VBO_H
#define VBO_H

#include <stdio.h>
#include <glad/glad.h>


typedef struct {
    GLuint id;
    float *vs;
    GLenum vusage;
    size_t vsize;
} VBO;

VBO vbo_init(float *vs, size_t vsize, GLenum vusage);
void vbo_create(VBO *vbo);
void vbo_update(VBO *vbo, float *vs, size_t vsize, GLenum vusage);
void vbo_bind(VBO *vbo);
void vbo_setData(VBO *vbo);
void vbo_unbind(VBO *vbo);
void vbo_clean(VBO *vbo);

#endif