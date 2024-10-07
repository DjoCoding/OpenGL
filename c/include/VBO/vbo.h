#ifndef VBO_H
#define VBO_H

#include <stdio.h>
#include <glad/glad.h>


typedef struct {
    GLuint id;
    void *vs;
    GLenum vusage;
    size_t vcount;
    size_t vsize;
} VBO;

VBO vbo_init(void *vs, size_t vsize, size_t vcount, GLenum vusage);
void vbo_create(VBO *vbo);
void vbo_update(VBO *vbo, void *vs, size_t vsize, size_t vcount, GLenum vusage);
void vbo_bind(VBO *vbo);
void vbo_setData(VBO *vbo);
void vbo_unbind(VBO *vbo);
void vbo_delete(VBO *vbo);

#endif