#include <MESH/mesh.h>

Mesh mesh_create(float *vs, size_t vcount, size_t vsize, GLenum vusage) {
    Mesh mesh = {0};
    mesh.vbo = vbo_init((void *) vs, vsize, vcount, vusage);
    return mesh;
}

void mesh_init(Mesh *this) {
    vbo_create(&this->vbo);
    vbo_setData(&this->vbo);

    vao_create(&this->vao);

    program_create(&this->prog);
    program_attach_shader(&this->prog, &this->vshader);
    program_attach_shader(&this->prog, &this->fshader);
    program_link(&this->prog); 
}

void mesh_design(Mesh *this, GLuint index, size_t component_num_items, GLenum component_item_type, GLboolean is_normalized, size_t offset) {    
    vao_set_layout_and_enable(&this->vao, &this->vbo, index, component_num_items, component_item_type, !is_normalized, this->vbo.vsize / this->vbo.vcount, offset);
}

void mesh_set_shader(Mesh *this, Shader shader, GLenum shader_type) {
    if (shader_type == GL_VERTEX_SHADER) {
        this->vshader = shader;
    }

    if (shader_type == GL_FRAGMENT_SHADER) {
        this->fshader = shader;
    }
}

void mesh_render(Mesh *this) {
    vbo_bind(&this->vbo);
    vao_bind(&this->vao);
    program_use(&this->prog);
    glDrawArrays(GL_TRIANGLES, 0, this->vbo.vcount);
}


void mesh_clean(Mesh *this) {
    vao_delete(&this->vao);
    vbo_delete(&this->vbo);
    program_delete(&this->prog);
}
