#include <VBO/vbo.h>

VBO vbo_init(void *vs, size_t vsize, size_t vcount, GLenum vusage) {
    VBO vbo = {0};
    vbo.vs = vs;
    vbo.vcount = vcount;
    vbo.vsize = vsize;
    vbo.vusage = vusage;
    return vbo;
}

void vbo_create(VBO *vbo) {
    glGenBuffers(1, &vbo->id);
}

void vbo_setData(VBO *vbo) {
    vbo_bind(vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo->vsize, vbo->vs, vbo->vusage);
    vbo_unbind(vbo);
}

void vbo_update(VBO *vbo, void *vs, size_t vsize, size_t vcount, GLenum vusage) {
    vbo->vs = vs;
    vbo->vcount = vcount;
    vbo->vsize = vsize;
    vbo->vusage = vusage;
}

void vbo_bind(VBO *vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
}

void vbo_unbind(VBO *vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_delete(VBO *vbo) {
    glDeleteBuffers(1, &vbo->id);
}

