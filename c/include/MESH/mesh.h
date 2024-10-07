#ifndef MESH_H
#define MESH_H

#include <VAO/vao.h>
#include <VBO/vbo.h>
#include <SHADER/shader.h>
#include <PROGRAM/program.h>

typedef struct {
    VBO vbo;
    VAO vao;
    Program prog;
    Shader vshader;
    Shader fshader;
} Mesh;

Mesh mesh_create(float *vs, size_t vcount, size_t vsize, GLenum vusage);
void mesh_design(Mesh *this, GLuint index, size_t component_num_items, GLenum component_item_type, GLboolean is_normalized, size_t offset);
void mesh_set_shader(Mesh *this, Shader shader, GLenum shader_type);
void mesh_init(Mesh *this);
void mesh_render(Mesh *this);
void mesh_clean(Mesh *this);


#endif