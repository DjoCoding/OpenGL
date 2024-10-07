#include <VAO/vao.h>


void vao_create(VAO *vao) {
    glGenVertexArrays(1, &vao->id);
}

void vao_bind(VAO *vao) {
    glBindVertexArray(vao->id);
}

void vao_unbind(VAO *vao) {
    glBindVertexArray(0);
}

void vao_set_layout_and_enable(VAO *vao, VBO *vbo, GLuint index, size_t num_items, GLenum item_type, GLboolean normalize_it, size_t vertext_size, size_t offset) {
    vao_bind(vao);
    vbo_bind(vbo);

    glVertexAttribPointer(index, num_items, item_type, normalize_it, vertext_size, (void*) offset);
    glEnableVertexAttribArray(index);

    vbo_unbind(vbo);
    vao_unbind(vao);
}

void vao_delete(VAO *vao) {
    glDeleteVertexArrays(1, &vao->id);
}