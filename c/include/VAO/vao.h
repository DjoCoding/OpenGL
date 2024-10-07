#ifndef VAO_H
#define VAO_H

#include <VBO/vbo.h>

typedef struct {
    GLuint id;
} VAO;

void vao_create(VAO *vao);
void vao_bind(VAO *vao);
void vao_unbind(VAO *vao);
void vao_set_layout_and_enable(VAO *vao, VBO *vbo, GLuint index, size_t num_items, GLenum item_type, GLboolean normalize_it, size_t vertex_size, size_t offset);
void vao_delete(VAO *vao);

#endif